import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class pass1 {
    public static void main(String[] args) throws Exception {
        FileReader fp = new FileReader("D:\\LP1-Practicals\\Assembler c++\\pass1\\input.txt");
        BufferedReader bufferReader = new BufferedReader(fp);

        int MAX = 101;

        // Pre-required tables for opcodes and directives
        Map<String, String> IsTab = new HashMap<>();
        Map<String, String> DsTab = new HashMap<>();
        Map<String, String> AdTab = new HashMap<>();

        // Initialize IsTab, DsTab, and AdTab
        // IMPERATIVE STATEMENTS
        IsTab.put("STOP", "00");
        IsTab.put("ADD", "01");
        IsTab.put("SUB", "02");
        IsTab.put("MULT", "03");
        IsTab.put("MOVER", "04");
        IsTab.put("MOVEM", "05");
        IsTab.put("COMP", "06");
        IsTab.put("BC", "07");
        IsTab.put("DIV", "08");
        IsTab.put("READ", "09");
        IsTab.put("PRINT", "10");

        // DECLARATIVE STATEMENTS
        DsTab.put("DS", "02");
        DsTab.put("DC", "01");

        // ASSEMBLER DIRECTIVES
        AdTab.put("ORIGIN", "03");
        AdTab.put("EQU", "04");
        AdTab.put("END", "02");
        AdTab.put("START", "01");
        AdTab.put("LTORG", "05");

        String[][] SymTab = new String[MAX][3];
        String[][] LitTab = new String[MAX][3];
        String[][] OpTab = new String[MAX][3];
        int[] PoolTab = new int[MAX];

        String line;
        int symline = 0, litline = 0, optabline = 0, poolIndex = 0;
        int LC = 0, linecnt = 0;

        // To store intermediate code (IC)
        List<String> intermediateCode = new ArrayList<>();

        System.out.println("--------CODE----------");

        while ((line = bufferReader.readLine()) != null) {
            String[] tokens = line.split("\t");

            // Print the current line
            System.out.println(line);

            if (tokens.length == 0) {
                System.out.println("Warning: Empty line encountered. Skipping.");
                continue;
            }

            if (linecnt == 0) {
               if (tokens.length > 1) {
                  LC = Integer.parseInt(tokens[1]);
               }
               linecnt++;
               continue;
            }

            // Process non-empty lines
            String label = tokens[0];
            String opcode = tokens.length > 1 ? tokens[1] : "";

            // Store Intermediate Code: Starting with the line counter
            StringBuilder icEntry = new StringBuilder(Integer.toString(LC));

            // Handle label
            if (!label.isEmpty()) {
                SymTab[symline][0] = label;
                SymTab[symline][1] = Integer.toString(LC);
                symline++;
            }

            // Handle opcode
            if (!opcode.isEmpty()) {
                icEntry.append("\t").append(opcode);

                // Handle Declarative Statements (DS, DC)
                if (opcode.equalsIgnoreCase("DS") || opcode.equalsIgnoreCase("DC")) {
                    if (tokens.length > 2) {
                        SymTab[symline - 1][2] = tokens[2];  // Store the value for DS/DC
                        icEntry.append("\t").append(tokens[2]);
                    }
                    LC++;
                }
                // Handle Literals
                else if (tokens.length > 2) {
                    String[] t2 = tokens[2].split(",");
                    if (t2.length > 1 && t2[1].charAt(0) == '=') {
                        LitTab[litline][0] = t2[1];
                        litline++;
                        icEntry.append("\t").append(t2[1]);
                    }
                }

                // Handle Assembler Directives
                if (opcode.equals("LTORG") || opcode.equals("END")) {
                    for (int i = poolIndex; i < litline; i++) {
                        if (LitTab[i][1] == null) {
                            LitTab[i][1] = Integer.toString(LC);
                            LC += 1;
                        }
                    }
                    PoolTab[poolIndex++] = litline;  // Update PoolTab
                } else if (opcode.equals("START")) {
                    if (tokens.length > 2) {
                        LC = Integer.parseInt(tokens[2]);
                        icEntry.append("\t").append(tokens[2]);
                    }
                } else if (opcode.equals("EQU")) {
                    String labelparam = tokens[2];
                    int rows = SymTab.length;
                    // Find the symbol in the symbol table and get its address
                    for (int i = 0; i < rows; i++) {
                        if (SymTab[i][0] != null && SymTab[i][0].equals(labelparam)) {
                            LC = Integer.parseInt(SymTab[i][1]);
                            break;
                        }
                    }
                    // Add the new label to the symbol table with the found address
                    SymTab[symline - 1][0] = label;
                    SymTab[symline - 1][1] = Integer.toString(LC);
                    symline++;
                } else if (opcode.equals("ORIGIN")) {
                    String expr = tokens[2];
                    if (expr.contains("+") || expr.contains("-")) {
                        String[] parts = expr.split("\\+|-");
                        String sym = parts[0].trim();
                        int value = Integer.parseInt(parts[1]);
                        for (int i = 0; i < symline; i++) {
                            if (SymTab[i][0].equals(sym)) {
                                LC = Integer.parseInt(SymTab[i][1]) + value;
                                break;
                            }
                        }
                    }
                } else if (IsTab.containsKey(opcode)) {
                    OpTab[optabline][0] = opcode;
                    OpTab[optabline][1] = "IS";
                    OpTab[optabline][2] = IsTab.get(opcode);
                    LC++;
                    optabline++;
                }
            }

            // Add the current IC entry to the list
            intermediateCode.add(icEntry.toString());
        }

        bufferReader.close();

        // Display Intermediate Code
        System.out.println("\n--------INTERMEDIATE CODE----------");
        for (String ic : intermediateCode) {
            System.out.println(ic);
        }

        // Display SymTab
        System.out.println("\n--------SYMBOL TABLE----------");
        System.out.println("Label\tAddress\tValue");
        for (int i = 0; i < symline; i++) {
            if (SymTab[i][0] != null) {
                System.out.println(SymTab[i][0] + "\t" + SymTab[i][1] + "\t" + (SymTab[i][2] != null ? SymTab[i][2] : ""));
            }
        }

        // Display LitTab
        System.out.println("\n--------LITERAL TABLE----------");
        System.out.println("Literal\tAddress");
        for (int i = 0; i < litline; i++) {
        	 if (LitTab[i][1] == null) {
        		 LitTab[i][1]=Integer.toString(LC);
             }
            if (LitTab[i][0] != null) {
                System.out.println(LitTab[i][0] + "\t" + LitTab[i][1]);
            }
        }

        // Display OpTab
        System.out.println("\n--------OPCODE TABLE----------");
        System.out.println("Opcode\tType\tValue");
        for (int i = 0; i < optabline; i++) {
            if (OpTab[i][0] != null) {
                System.out.println(OpTab[i][0] + "\t" + OpTab[i][1] + "\t" + OpTab[i][2]);
            }
        }
    }
}
