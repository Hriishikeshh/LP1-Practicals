def macro_Pass1(inputlines):
    mnt=[]
    mdt=[]
    kpdt=[]
    pntab={}
    ic=[]

    Macroname=None
    mdtp=1
    kpdtp=0
    paramNo=1
    pp=0
    kp=0
    flag=0

    for line in inputlines:
        line=line.strip()
        parts=line.split()
        if parts[0].upper()=="MACRO":
            flag=1
            continue
        elif flag==1:
            Macroname=parts[0]
            pp=kp=paramNo=1
            pntab[Macroname]=[]
            if(len(parts)>1):
                for i in range(1,len(parts)):
                    param=parts[i].replace("&","").replace(",","")
                    if "=" in param:
                        kp+=1
                        keyword_param=param.split("=")
                        pntab[Macroname].append(keyword_param[0])
                        kpdt.append((keyword_param[0],keyword_param[1] if len(keyword_param)>1 else "-"))
                    else:
                        pntab[Macroname].append(param)
                        pp+=1
            mnt.append((Macroname,pp,kp,mdtp,kpdtp if kp==0 else kpdtp+1))
            kpdtp+=kp
            flag=2
        elif flag==2:
            if parts[0].upper()=="MEND":
                mdt.append("MEND")
                flag=0
            else:
                mdt_line=[]
                for part in parts:
                    if "&" in part:
                        part=part.replace("&","").replace(",","")
                        mdt_line.append(f"(P,{pntab[Macroname].index(part)+1})")
                    else:
                        mdt_line.append(part)
                mdt.append(" ".join(mdt_line))
                mdtp+1
        else:
            ic.append(line)
    return mdt,mnt,kpdt,pntab,ic

with open("Macroprocessor\pass1\input.txt",'r') as file:
    input_lines=[line.strip() for line in file]

mdt,mnt,kpdt,pntab,ic=macro_Pass1(input_lines)

with open("MDT.txt",'w') as file:
    print("\nMacro Definition Table\n")
    file.write("Macro Definition Table\n")
    for entry in mdt:
        print(entry)
        file.write(f"{entry}\n")

with open("MNT.txt",'w') as file:
    print("\nMacro Name Table\n")
    file.write("Macro Name Table\n")
    for entry in mnt:
        print(entry)
        file.write(f"{entry}\n")

with open("KPDT.txt",'w') as file:
    print("\nKeyword Parameter Table\n")
    file.write("Keyword Parameter Table\n")
    for entry in kpdt:
        print(entry)
        file.write(f"{entry}\n")

with open("PNTAB.txt",'w') as file:
    print("\nParameter Table\n")
    file.write("Parameter Table\n")
    for key,value in pntab.items():
        print(f"{key}\t{value}")
        file.write(f"{key}\t{value}\n")

with open("IC.txt",'w') as file:
    print("\nIntermediate Code\n")
    file.write("Intermediate Code\n")
    for entry in ic:
        print(entry)
        file.write(f"{entry}\n")
