# -*- coding: utf-8 -*-

if __name__ == "__main__":

    ### Print CLM_LIBS STATS ##################################################

    with open("CLM_LIBS.h", "r") as source: lines = source.readlines()

    n_lines   = len(lines)
    LOC       = 0
    functions = 0
    macros    = 0
    date      = ""
    for line in lines:
        line = line.replace("\n", "")
        line = line.replace("\\", "")
        if "#define CLM_LIBS " in line: date = line[line.index("CLM_LIBS")+9:]
        while "/*" in line:
            line = line[line.index("/*")+2:line.index("/*")+2]
        if "static inline" in line: functions += 1
        if "#define" in line: macros += 1
        line = line.replace(" ", "")
        if line: LOC += 1

    print("")
    print("\tVersion:   "+date[6:8]+"/"+date[4:6]+"/"+date[0:4])
    print("\tLibraries: "+str(macros-1))
    print("\tFunctions: "+str(functions))
    print("\tLOC/total: "+str(LOC)+" / "+str(n_lines)+" ("
                         +str(round(100*LOC/float(n_lines),2))+"%)\n")


    ### Preprocess CLM_LIBS ###################################################

    #with open("CLM_LIBS.h", "r") as source: lines = source.readlines()

    TOC = []

    for numline, line in enumerate(lines):

        if line.endswith("\n"):  line = line.replace("\n", "")
        if line.endswith(" \\"): line = line.replace(" \\", "")
        if "/** " in line:       line = line.lstrip()
        lines[numline] = line[:]

        if line.startswith("/** ##"):
            line = line.replace(" **/", "")
            line = line.rstrip()
            TOC.append(((line.count("#")-2)*" ")+"* "+line[2+line.index("# "):])

    ### Print README.md #######################################################

    with open("README.md", "w") as output:

        for numline, line in enumerate(lines):

            if line.startswith("#include <"):
                i    = line.index(">")
                line = line[:i+1] + "\n"
                if not lines[numline-1].startswith("#include <"):
                    output.write("```c\n")
                output.write(line)
                if not lines[numline+1].startswith("#include <"):
                    output.write("```\n")

            elif line.startswith("/** "):

                line = line.replace("/** ", "")
                line = line.replace(" **/", "")
                line = line.rstrip()

                if not line.startswith("    ") and "<" in line and ">" in line:
                    i = line.index("<")
                    j = line.index(">")
                    URL = line[i+1:j]
                    if URL.startswith("http"):
                        line = line[:i]+"["+URL+"]("+URL+")"+line[j+1:]
                    else:
                        line = line[:i]+"["+URL+"](#"+URL.replace(" ","-")+")"+line[j+1:]

                if line.startswith("# "):     line = line.replace("_", "\_")
                if line.startswith("## "):    line = line.replace("_", "\_"); line += " [⯅](#CLM_LIBS)"
                if line.startswith("### "):   line = line.replace("_", "\_"); line += " [⯅](#CLM_LIBS)"
                if line.startswith("#### "):  line = line.replace("_", "\_"); line += " [⯅](#CLM_LIBS)"
                if line.startswith("##### "): line = line.replace("_", "\_"); line += " [⯅](#CLM_LIBS)"

                line += "\n"

                if line.startswith("    "):
                    if not lines[numline-2].startswith("/**     "): output.write("```c\n")
                    output.write(line[4:])
                    if not lines[numline+2].startswith("/**     "): output.write("```\n")
                else:
                    output.write(line)

                    if "**SOURCE:**" in line:
                        output.write("\n**TABLE OF CONTENTS:**\n\n")
                        for row in TOC:
                            if row.startswith("*") or row.startswith(" *"):
                                URL = row.strip()
                                URL = URL.replace("* ", "")
                                URL = URL.replace(" ", "-")
                                row = row.replace("_", "\_")
                                row = row.replace("* ", "* [")
                                row = row.replace(" *", "    *")
                                if URL == "CLM_LIBS": URL += "-1"
                                output.write(row+"](#"+URL+"-)\n")

                if line.startswith("### "):
                    diff = 1
                    while not lines[numline+diff].startswith("  #define"): diff += 1
                    define  = lines[numline+diff].strip()
                    define += "\n"
                    output.write("\n```c\n"+define+"```\n")

                if line.startswith("#### "):
                    diff = 1
                    while (not lines[numline+diff].startswith("    static inline")
                           and not lines[numline+diff].startswith("    typedef")):
                            diff += 1
                    num   = numline + diff
                    proto = lines[num].strip()
                    if proto.startswith("typedef"):
                        proto  = proto.strip()
                        proto += "\n"
                        diff   = 1
                        while not lines[num+diff].startswith("            "):
                            proto += (lines[num+diff][4:]).rstrip()
                            proto += "\n"
                            diff  += 1
                        proto = proto.replace("prefix##", "")
                        output.write("\n```c\n" + proto + "```\n")
                    else:
                        diff = 1
                        while "{" not in proto:
                            proto += " "+(lines[num+diff]).strip()
                            diff  += 1
                        proto = proto.replace("prefix##", "")
                        proto = proto[:proto.index("{")+1]
                        proto = proto.replace(" {", ";")
                        proto += "\n"
                        output.write("\n```c\n"+proto+"```\n")

    ### Print CHEATSHEET.md ###################################################

    with open("CHEATSHEET.md", "w") as output:

        output.write("\n# CLM\_LIBS CHEAT SHEET\n\n```c")

        for numline, line in enumerate(lines):

            if line.startswith("  #define"):
                line = line.strip()
                line = "\n" + line + "\n\n"
                output.write(line)

            elif line.startswith("    static inline"):
                line = line.strip()
                diff = 1
                while "{" not in line:
                    if line.endswith(","): line += " "
                    line += (lines[numline+diff]).strip()
                    diff += 1
                line = line.replace("static inline ", "")
                line = line.replace("prefix##", "")
                line = line.replace("const ", "")
                line = line[:line.index("{")+1]
                line = line.replace(" {", ";")

                type_names = ("void", "bool", "int", "size_t", "double", "char",
                              "stree", "clist", "array", "type", "wtree")
                tab = max(len(t)+1 for t in type_names)
                for type_name in type_names:
                    if line.startswith(type_name):
                        if line[len(type_name)+1:].startswith("*"): tab -= 1
                        tab -= len(type_name)
                        line = line.replace(type_name, type_name+tab*" ", 1)

                line = "    " + line + "\n"
                output.write(line)

            elif line.startswith("    typedef"):
                line  = line.rstrip()
                line += "\n"
                diff  = 1
                while not (lines[numline+diff]).startswith("            "):
                    line += (lines[numline+diff]).rstrip()
                    line += "\n"
                    diff += 1
                line = line.replace("prefix##", "")
                line += "\n"
                output.write(line)

        output.write("```\n\n")
