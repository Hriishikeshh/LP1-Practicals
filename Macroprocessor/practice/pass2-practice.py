class mntentry:
    def __init__(self,name,pp,kp,mdtp,kpdtp):
        self.name=name
        self.pp=pp
        self.kp=kp
        self.mdtp=mdtp
        self.kpdtp=kpdtp

mnt={
    "M1": mntentry("M1",2,2,1,1),
    "M2":mntentry("M2",2,2,6,3)
}

kpdt={
    1:{"B":"CREG"},
    2:{"A":"AREG","B":"CREG"},
    3:{"V":"AREG","U":"BREG"}  
}

mdt=[
    "MOVER\t(P,3),\t(P,1) ",
    "ADD\t(P,3),\t='1'",
    "MOVER\t(P,4),\t(P,2)",
    "ADD\t(P,3)\t='1'",
    "MEND",
    "MOVER\t(P,3)\t(P,1)",
    "MOVER\t(P,4)\t(P,2)",
    "ADD\t(P,3)\t='15'",
    "ADD\t(P,4)\t='10'",
    "MEND"
]

ic=[
"START 100",
"M1 10,20,&B=CREG",
"M2 100,200,&V=AREG,&U=BREG",
"END"
]

def macro_expansion():
    aptab={}
    aptab_inverse={}
    output=[]

    for lines in ic:
        parts=lines.split()
        if(parts[0] in mnt):
            # get macro details from mnt
            macro_name=parts[0]
            entry=mnt[macro_name]
            name,pp,kp,mdtp,kpdtp=entry.name,entry.pp,entry.kp,entry.mdtp,entry.kpdtp

            # get positional parameters
            parameters=parts[1].split(',')
            param_no=1
            for i in range(pp):
                aptab[param_no]=parameters[i].replace(',','')
                aptab_inverse[aptab[param_no]]=param_no
                param_no+=1
            
            # get keyword parameters
            j=kpdtp
            kpdtp_entry=kpdt[j]

            for key,default_value in kpdtp_entry.items():
                aptab[param_no]=default_value
                aptab_inverse[key]=param_no
                param_no+=1

            # get keyword parameters passed from ic
            for i in range(pp,len(parameters)):
                parameters_split=parameters[i].split("=")
                param_key=parameters_split[0].replace("&","")
                param_val=parameters_split[1]
                aptab[aptab_inverse[param_key]]=param_val
            
            #generate the ic
            i=mdtp-1
            while mdt[i] != "MEND":
                mdt_parts=mdt[i].split("\t")
                expanded_line="+"
                
                for parts in mdt_parts:
                    if "(P" in parts:
                        index=int(parts.split("(P,")[1].split(")")[0])
                        expanded_line+=aptab.get(index,f"(P,{index})")+"\t"
                    else:
                        expanded_line+=parts+"\t"
                output.append(expanded_line.strip()) 
                i+=1
            print(parameters)
            print(aptab)
            print(aptab_inverse)
            aptab.clear()
            aptab_inverse.clear()

        else:
            output.append(lines)

    return output




# printing
expanded_code=macro_expansion()
for lines in expanded_code:
    print(lines)


with open("Macroprocessor\practice\mc.txt","w") as file:
    for lines in expanded_code:
        file.write(f"{lines}\n")




