Symtab={}
Littab=[]
Pooltab=[0]
LC=0
IC=[]

IS={"STOP":0,"ADD":1,"SUB":2,"MUL":3,"MOVER":4,"MOVEM":5,"COMP":6,"BC":7,"DIV":8,"READ":9,"PRINT":10}
AD={"START":1,"END":2,"ORIGIN":3,"EQU":4,"LTORG":5}
DL={"DC":1,"DS":2}
REG={"AREG":1,"BREG":2,"CREG":3,"DREG":4}

def read_input_code(file_path):
    input_code=[]
    with open(file_path,'r') as file:
        for line in file:
            parts=[part.strip() for part in line.split(',')]
            input_code.append(parts)
    return input_code

Inputcode=read_input_code('input.txt')

def set_input(inputcode):
    global inputs
    inputs=inputcode

def pass1():
    global IC,LC
    for label,opcode,op1,op2 in inputs:
        if label and label!='-':
            Symtab[label]=LC
        if opcode in IS:
            IC.append(f"(IS,{IS[opcode]}) {get_opcode(op1)} {get_opcode(op2)}")
            LC+=1
        elif opcode in AD:
            IC.append(f"(AD,{AD[opcode]}) {get_opcode(op1)} {get_opcode(op2)}")
            handle_ad_directives(opcode,op1)
        elif opcode in DL:
            IC.append(f"(DL,{DL[opcode]}) {get_opcode(op1)}")
            LC+=1 if opcode=="DC" else int(op1)

def handle_ad_directives(opcode,op1):
    global LC
    if opcode=="START":
        LC=int(op1)
    elif opcode=="END" or opcode=="LTORG":
        processLiterals()
    elif opcode=="ORIGIN":
        LC=eval_expr(op1)
    elif opcode=="EQU":
        Symtab[op1]=eval_expr(op1)

def get_opcode(operand):
    if operand=="-":
        return ""
    elif operand in REG:
        return f"(R,{REG[operand]}"
    elif operand.startswith("="):
        Littab.append((operand,-1))
        return f"(L,{len(Littab)}"
    elif operand.isdigit():
        return f"(C,{operand})"
    else:
        return f"(S,{Symtab.get(operand,0)+1})"

def eval_expr(expr):
    return int(expr) if expr.isdigit() else Symtab.get(expr,0)

def processLiterals():
    global LC
    for i in range(Pooltab[-1],len(Littab)):
        Littab[i]=(Littab[i][0],LC)
        LC+=1
    Pooltab.append(len(Littab))

def show_tables():
    print("Intermediate Code")
    for code in IC:
        print(code)

    print("Symbol Table")
    for key,value in Symtab.items():
        print(f"{key}\t{value}")


    print("Literal Table")
    for literal in Littab:
        print(f"{literal[0]}\t{literal[1]}")


    print("Pool Table")
    for PoolIndex in Pooltab:
        print(PoolIndex)

def show_files():
    with open("ic.txt","w") as file:
        file.write("Intermediate Code\n")
        for code in IC:
            file.write(f"{code}\n")
    with open("st.txt","w") as file:
        for key,value in Symtab.items():
            file.write(f"{key}\t{value}\n")
    with open("lt.txt","w") as file:
        for literal in Littab:
            file.write(f"{literal[0]}\t{literal[1]}\n")
    with open("pt.txt","w") as file:
        for poolIndex in Pooltab:
            file.write(f"{poolIndex}\n")

set_input(Inputcode)
pass1()
show_tables()
show_files()






