# MACRO
# M1 &X, &Y, &A=AREG, &B=
# MOVER &A, &X
# ADD &A, ='1'
# MOVER &B, &Y
# ADD &B, ='5'
# MEND
# MACRO
# M2 &P, &Q, &U=CREG, &V=DREG
# MOVER &U, &P
# MOVER &V, &Q
# ADD &U, ='15'
# ADD &V, ='10'
# MEND
# START 100
# M1 10, 20, &B=CREG
# M2 100, 200, &V=AREG, &U=BREG
# END


class MNTEntry:
    def __init__(self,name,pp,kp,mdtp,kpdtp):
        self.name=name
        self.pp=pp
        self.kp=kp
        self.mdtp=mdtp
        self.kpdtp=kpdtp

mnt = {
    "M1": MNTEntry("M1", 2, 2, 1, 1),
    "M2": MNTEntry("M2", 2, 2, 6, 3)
}
kpdt={
    1:{"B":"CREG"},
    2:{"A":"AREG","B":"CREG"},
    3:{"V":"AREG","U":"BREG"}
}

mdt=[
"MOVER\t(P,3)\t(P,1)",
"ADD\t(P,3)\t='1'",
"MOVER\t(P,4)\t(P,2)",
"ADD\t(P,4)\t='5'",
"MEND",
"MOVER\t(P,3)\t(P,1)",
"MOVER\t(P,4)\t(P,2)",
"ADD\t(P,3)\t='15'",
"ADD\t(P,4)\t='10'",
"MEND"
]

ic=[
"START 100",
"M1 10, 20, &B=CREG",
"M2 100, 200, &V=AREG, &U=BREG",
"END"
]

def Macro_Expansion():
    aptab={}
    aptab_inverse={}
    output=[]

    for line in ic:
        parts=line.split()
        if parts[0] in mnt:
            # search macro name in mnt and retrieve data from mnt
            macro_name=parts[0]
            entry=mnt[macro_name]
            pp,kp,mdtp,kpdtp=entry.pp,entry.kp,entry.mdtp,entry.kpdtp
            
            # handle positional parameters
            params=parts[1].split(',')
            param_No=1
            for i in range(pp):
                aptab[param_No] = params[i].replace(",", "")
                aptab_inverse[aptab[param_No]] = param_No
                param_No += 1

            # handle keyword parameters getting all default values in the array
            j = kpdtp
            kpdt_entry = kpdt[j]
            for key, default_value in kpdt_entry.items():         
                aptab[param_No] = default_value
                aptab_inverse[key] = param_No
                param_No += 1

            # get all passed keyword parameters value fro ic
            for i in range(pp, len(params)):
                param_split = params[i].split("=")
                param_name = param_split[0].replace("&", "")
                param_value = param_split[1]
                aptab[aptab_inverse[param_name]] = param_value
            
            i = mdtp - 1

            while mdt[i] != "MEND":
                mdt_parts = mdt[i].split("\t")
                expanded_line = "+"

                for part in mdt_parts:
                    # Check if part references a parameter (e.g., "(P,n)")
                    if "(P," in part:
                        # Extract the index value n from (P,n)
                        index = int(part.split("(P,")[1].split(")")[0])

                        # Replace (P,n) with the actual parameter value from aptab
                        expanded_line += aptab.get(index, f"(P,{index})") + "\t"
                    else:
                        # Add non-parameter parts as-is
                        expanded_line += part + "\t"

                # Append the expanded line without trailing spaces
                output.append(expanded_line.strip())
                i += 1

            aptab.clear()
            aptab_inverse.clear()
        else:
            output.append(line)
    return output

# printing answer
expanded_code=Macro_Expansion()
for line in expanded_code:
    print(line)

with open("Macroprocessor/pass2/MC.txt",'w') as file:
    file.write("Machine Code\n")
    for line in expanded_code:
        file.write(f"{line}\n")



