class Pass2:
    def __init__(self,symtab,littab,pooltab,ic):
        self.Symtab=symtab
        self.Littab=littab
        self.Pooltab=pooltab
        self.IC=ic
        self.MachineCode=[]

    def pass2(self):
        for line in self.IC:
            tokens=line.split()
            if tokens[0].startswith("(IS"):
                opcode=tokens[0][4]
                reg=self.getValue(tokens[1]) if len(tokens)>1 else ""
                operand=self.getValue(tokens[2]) if len(tokens)>2 else ""
                self.MachineCode.append(f"{opcode} {reg}  {operand}")
            elif tokens[0].startswith("(DL"):
                if tokens[0]=="(DL,1)":
                    self.MachineCode.append(f"00 00 {tokens[1][3:-1]}")
                elif tokens[0]=="(DL,2)":
                    self.MachineCode.append(f"00 00 00")
            elif tokens[0].startswith("(AD"):
                continue
    def getValue(self,token):
        if token.startswith("(R,"):
            return token[3]
        elif token.startswith("(C,"):
            return token[3:-1]
        elif token.startswith("(S,"):
            symIndex=int(token[3:-1])
            if symIndex in self.Symtab:
                return str(self.Symtab[symIndex])
            else:
                raise KeyError(f"Symbol Index {symIndex} not found in Symtab")
        elif token.startswith("(L,"):
            litIndex=int(token[3:-1])-1
            return str(self.Littab[litIndex][1])

    def show_MachineCode(self):
        print("Machine Code")
        for code in self.MachineCode:
            print(code)

    def show_MCFile(self):
        with open("mc.txt",'w') as file:
            file.write("Machine Code\n")
            for code in self.MachineCode:
                file.write(f"{code}\n")

if __name__=="__main__":
    symtab={
        1: 104,
        2: 113,
        3: 114,
        4: 115,
        5: 116,
        6: 117
    }
    littab=[
        ("=1", 118),
        ("=2", 119)
    ]
    pooltab=[0,2]
    IC=[
        "(AD,1) (C,101)",
        "(IS,9) (S,1)",
        "(IS,4) (R,2) (S,1)",
        "(IS,5) (R,2) (S,1)",
        "(IS,4) (R,3) (S,1)",
        "(IS,1) (R,3) (S,1)",
        "(IS,5) (R,3) (S,1)",
        "(IS,6) (R,3) (S,1)",
        "(IS,7) (S,1) (S,1)",
        "(IS,8) (R,2) (S,1)",
        "(IS,5) (R,2) (S,1)",
        "(IS,10) (S,1)",
        "(IS,0)",
        "(DL,2) (C,1)",
        "(DL,2) (C,1)",
        "(DL,1) (L,1)",
        "(DL,2) (C,1)",
        "(DL,1) (L,2)",
        "(AD,2)"
    ]
    asmp2=Pass2(symtab,littab,pooltab,IC)
    asmp2.pass2()
    asmp2.show_MachineCode()
    asmp2.show_MCFile()



