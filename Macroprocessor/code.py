file = []
with open("Macroprocessor/input.txt", "r") as f:
    file = f.readlines()


with open("Macroprocessor/mdt.txt", "w") as mdt:
    with open("Macroprocessor/mnt.txt", "w") as mnt:
        with open("Macroprocessor/ic.txt", "w") as ic:
            ala = []
            mdtp = 1
            flag = 0

            for line in file:
                l = line.strip()  
                if l == "MACRO":
                    flag = 1
                elif l == "MEND":
                    mdt.write(l + "\n")
                    mdtp += 1
                    flag = 0
                elif flag == 1:
                    mdt.write(l + "\n")
                    temp = l.split()
                    mnt.write(temp[0] + " " + str(mdtp) + "\n")
                    ala = temp[1].split(",")
                    mdtp += 1  
                    flag = 2 
                elif flag == 2:
                    temp = l.split()
                    part2 = temp[1].split(",")
                    mdt.write(temp[0] + " ")
                    for i in part2:
                        for j in range(len(ala)):
                            t = ala[j].split("=")
                            if t[0] == i:
                                mdt.write("#" + str(j) + ",")
                    mdt.write("\n")
                    mdtp += 1  
                else:
                    ic.write(line)

print(f"MDT lines: {mdtp}")