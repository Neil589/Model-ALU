#define CONFIG_ERROR 1
#define OK 0

// ----------------------------------------
// Simulate add and subtract arithmetic digital logic circuit
// 
// ----------------------------------------

typedef struct {
    int A;			// 32 bit input
    int B;			// 32 bit input
    int Y;			// 32 bit output
    char Sub;			// ALUFN: Sub = 0 or 1
} arithmetic;

void arithmetic_fun_exe(arithmetic* circuit);
int arithmetic_fun_cfg(arithmetic* circuit);

// ----------------------------------------
// Simulate shifting digital logic circuit
// 
// ----------------------------------------

typedef struct {
    int A;			// 32 bit input
    int B;			// 32 bit input
    int Y;			// 32 bit output 
    char* Bool;			// ALUFN: Bool = 00, 01, 10, or 11
} shift;

void shift_fun_exe(shift* circuit);
int shift_fun_cfg(shift* circuit);

// ----------------------------------------
// Simulate boolean logic digital logic circuit
// 
// ----------------------------------------

typedef struct {
    int A;			// 32 bit input
    int B;			// 32 bit input
    int Y;			// 32 bit output
    char* Bool;			// ALUFN: Bool = 00, 01, 10, or 11
} logic;

void logic_fun_exe(logic* circuit);
int logic_fun_cfg(logic* circuit);


// ----------------------------------------
// Simulate multiplexor (MUX) digital logic circuit
// 
// ----------------------------------------
typedef struct {
    int A;			// 32 bit input
    int B;			// 32 bit input
    int Y;			// 32 bit output
    char Selector;		// ALUFN: MUX selector bit
} mux;

void mux_fun_exe(mux* circuit);
int mux_fun_cfg(mux* circuit);

// ----------------------------------------
// Global variables that simulate MUX, shift, logic, and 
// arthmetic hardware components.
// 
// ----------------------------------------
mux* math_mux;
mux* shft_mux;
shift* shift_circuit;
logic* logic_circuit;
arithmetic* arithmetic_circuit;

// ----------------------------------------
// Initialize the simulated MUX, shift, logic, and arithmetic
// hardware components.
//
// args:
//			None
//
// return:
//			None
// ----------------------------------------
void initialize_alu();

// ----------------------------------------
// Configure ALU using ALUFN bits
// In our simulator a configuration bit is represented by 
// an 8-bit ASCII character value (per the 5-bit ALUFN Table)
//
// args:
//			Sub = add or subtract circuit configuration bits
//			Bool = shifter and boolean circult configuration bits
//			Shft = MUX selector bit
//			Math = MUX selector bit
//
// return:
//			CONFIG_ERROR for an unsupported configuration value
//        	OK when all configuration values are correct
// ----------------------------------------
int configure_alu(char Sub, char* Bool, char Shft, char Math);

// ----------------------------------------
// Run ALU
//
// args:
//			A = signed 2's complement 32 bit integer value
//			B = signed 2's complement 32 bit integer value
//
// return:
//			Result = signed 2's complement 32 bit integer value
// ----------------------------------------
int run_alu(int A, int B);

