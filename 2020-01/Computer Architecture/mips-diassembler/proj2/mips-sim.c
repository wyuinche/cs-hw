/* Header */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Instruction Unit */
#define INSTRUCTION_UNIT 32
#define OPCODE_UNIT 6
#define REGIST_UNIT 5
#define SHAMT_UNIT 5
#define FUNCT_UNIT 6
#define IMMED_UNIT 16
#define ADDRESS_UNIT 26

/* Command Code */
#define READ 10
#define EXIT 11
#define LOAD 12
#define RUN 13
#define REGISTERS 14

/* Instruction Code */
#define R_TYPE 0
#define I_TYPE 1
#define J_TYPE 2
#define WRONG_INSTRUCTION 4

/* R Type Instruction Code */
#define R_DST 40
#define R_DTS 41
#define R_S 42
#define R_D 43
#define R_ST 44
#define R_DTSA 45
#define R_SYSCALL 46
#define R_DS 47

/* I Type Instruction Code */
#define I_TSIM 50
#define I_STOFF 51
#define I_TOFFS 52
#define I_TIM 53

/* Error Code */
#define COMMAND_ERROR 21 
#define FILE_ERROR 22
#define DISASSEMBLE_ERROR 23
#define LOAD_ERROR 24
#define RUN_BOUND_ERROR 25

/* Print Code */
#define BYTE_F 30
#define BIT_F 31
#define SIGNED 32
#define UNSIGNED 33

/* Proj2 Def */
/* Memory Size */
#define REGIST_N 32
#define INST_MEMORY_N 65536

/* Instruction Structure */
typedef struct {
	int flag;
	int opcode_int;
	char instruction[4];
	char opcode[OPCODE_UNIT];
	char rs[REGIST_UNIT];
	char rt[REGIST_UNIT];
	char rd[REGIST_UNIT];
	char shamt[SHAMT_UNIT];
	char funct[FUNCT_UNIT];
	char immediate[IMMED_UNIT];
	char address[ADDRESS_UNIT];
} INSTRUCTION;	

/* Register Memory */
typedef struct {
	char bit[32];
} REGISTER;
REGISTER generalRegisters[REGIST_N];
REGISTER pcRegister;
unsigned int pc;

/* Instruction Memory */
char InstructionMemory[INST_MEMORY_N]; 

/* Command Variables */
char command[100];
char fileName[100];
int N_inst;

/* Init Memory (proj 2) */
void InitGeneralRegist();
void InitPCRegist();
void InitRegist();
void InitInstMemory();
void InitMemory();

/* Functions 1 */
int pow_2(int);
void clearBuffer();
void printError(int);

/* Functions 2 */
int interpretCommand();

/* READ command Functions */
/* Functions 3 */
int Disassemble(FILE*);
void decomposeInstruction(INSTRUCTION*, char*);
void ByteToBit(char*, char*);
int BitToInt(char*, int, int);
void decomposeRTYPE(INSTRUCTION*, char*);
void decomposeITYPE(INSTRUCTION*, char*);
void decomposeJTYPE(INSTRUCTION*, char*);
void copyInstruction(char*, char*, int);
/* Functions 4 */
void printInstruction(INSTRUCTION*, int);
void printUnknownInstruction();
void printInHex(char*, int, int);
void printRTYPE(INSTRUCTION*);
void printITYPE(INSTRUCTION*);
void printJTYPE(INSTRUCTION*);
/* Functions 5 */
void printRTYPEcode(INSTRUCTION*, int, int);
void printITYPEcode(INSTRUCTION*, int);
void printJTYPEcode(INSTRUCTION*, int);
int checkZero(char*, int);

/* LOAD command Functions */
/* Function 6 */
int LoadInstruction(FILE*);

/* RUN command Functions */
/* Function 7 */
int RunInstruction(int);
int interpretInst(char*, int*);
int runInst(char*, int, int);
int runRTYPE(char*, int);
int runITYPE(char*, int);
void shiftLogic(int, int, int, char);
void shiftArith(int, int, int, char);
void add(int, int, int);
void addi(int, int, int);
void sub(int, int, int);
void slt(int, int, int, int);
void slti(int, int, char*, int);
void updatePC();

/* REGISTERS command Functions */
void printRegist();

int main(int argc, const char* argv[]){
	FILE* fp;
	int commandCode;
	int resultCode;

	InitMemory();

	while(1){
		printf("mips-sim> ");
		scanf("%s", command);
		if(!strcmp(command, "read")||!strcmp(command, "loadinst")) scanf("%s", fileName);
		else if(!strcmp(command, "run")) scanf("%d", &N_inst);
		clearBuffer();

		commandCode = interpretCommand();
		switch(commandCode){
		case READ:
			fp = fopen(fileName,"rb");
			resultCode = Disassemble(fp);
			printError(resultCode);
			if(resultCode!=FILE_ERROR) fclose(fp);
			break;
		case LOAD:
			fp = fopen(fileName, "rb");
			resultCode = LoadInstruction(fp);
			printError(resultCode);
			if(resultCode!=FILE_ERROR) fclose(fp);
			break;
		case RUN:
			resultCode = RunInstruction(N_inst);
			printError(resultCode);
			break;
		case REGISTERS: printRegist(); continue;
		case EXIT: return 0;
		default: printError(COMMAND_ERROR); continue;
		}
	}

	return 0;
}

void printRegist(){
	int i;
	for(i=0; i<REGIST_N; i++){
		printf("$%d: 0x", i);
		printInHex(generalRegisters[i].bit, REGIST_N, BIT_F);
		putchar('\n');
	}
	printf("PC: 0x");
	printInHex(pcRegister.bit, REGIST_N, BIT_F);
	putchar('\n');
}

/* Calculate Power of 2 */
int pow_2(int n){
	if(n<1) return 1;
	return pow_2(n-1)*2;
}

/* Clear Input Buffer */
void clearBuffer(){
	while(getchar()!='\n');
}

/* print Error */
void printError(int code){
	switch(code){
	case COMMAND_ERROR: printf("[ERROR] Command Error\n"); break;
	case FILE_ERROR: printf("[ERROR] Can't Open File\n"); break;
	case DISASSEMBLE_ERROR: printf("[ERROR] Disassemble Failure\n"); break;
	case LOAD_ERROR: printf("[ERROR] Fail Load Instructions\n"); break;
	case RUN_BOUND_ERROR: printf("[ERROR] Your Command: run N (N is Out of Instruction Memory\n"); break;
	default: return;
	}
}

/* Get Command(READ, or EXIT) and File Name */
int interpretCommand(){
	if(!strcmp(command, "read")) return READ;
	else if(!strcmp(command, "loadinst")) return LOAD;
	else if(!strcmp(command, "run")) return RUN;
	else if(!strcmp(command, "registers")) return REGISTERS;
	else if(!strcmp(command, "exit")) return EXIT;
	return COMMAND_ERROR;
}

/* Disassemble the file */
int Disassemble(FILE *fp){
	INSTRUCTION *target;
	char targetInstruction[INSTRUCTION_UNIT];
	int buf_l;
	int i, count=0;
	
	if(fp==NULL) return FILE_ERROR;
	target = (INSTRUCTION*)malloc(sizeof(INSTRUCTION));	

	while(!feof(fp)){
		if(buf_l=fread(target->instruction, sizeof(char), 4, fp)<4){
			return 0;
		}
		ByteToBit(targetInstruction, target->instruction);
		decomposeInstruction(target, targetInstruction);
		printInstruction(target, count++);	
	}	

	free(target);
	return 0;
}

/* Binary Expression of Target */
void ByteToBit(char* des, char* src){
	unsigned int tmp[4];
	int i;

	for(i=0; i<4; i++) tmp[i] = (unsigned int)src[i];
	for(i=0; i<4; i++) if(tmp[i]>0x000000ff) tmp[i] ^= 0xffffff00;
	for(i=7; i>=0; i--){ des[i] = tmp[0]%2; tmp[0] /= 2; }
	for(i=15; i>=8; i--) { des[i] = tmp[1]%2; tmp[1] /= 2; }
	for(i=23; i>=16; i--) { des[i] = tmp[2]%2; tmp[2] /= 2; }
	for(i=31; i>=24; i--) { des[i] = tmp[3]%2; tmp[3] /= 2; }
}

/* Change Bit Expression # into Int */
int BitToInt(char* src, int n, int code){
	int i;
	int tmp=0;
	unsigned int tmp2=0;
	if(code==UNSIGNED&&n>=32){
		for(i=0; i<n; i++)
			tmp2 += src[i]*pow_2(n-1-i);
		return tmp2;
	}
	if(code==UNSIGNED)
		for(i=0; i<n; i++)
			tmp += src[i]*pow_2(n-1-i);
	else{
		for(i=1; i<n; i++)
			tmp += src[i]*pow_2(n-1-i);
		tmp -= src[0]*pow_2(n-1);
	}
	return tmp;
} 

/* Divide Instruction into each Part */ 
void decomposeInstruction(INSTRUCTION* target, char* instruction){
	int i;
	copyInstruction(target->opcode, instruction, OPCODE_UNIT);
	target->opcode_int = 0;
	target->opcode_int = BitToInt(target->opcode, OPCODE_UNIT, UNSIGNED);
	if(target->opcode_int==0) target->flag = R_TYPE;  
	else if(target->opcode_int==2||target->opcode_int==3) target->flag = J_TYPE;
	else{
		switch(target->opcode_int){
		case 4: case 5: case 8: case 9: case 10:
		case 11: case 12: case 13: case 14: case 15:
		case 32: case 33: case 35: case 36: case 37:
		case 40: case 41: case 43: target->flag = I_TYPE; break;
		default: target->flag = WRONG_INSTRUCTION;
		}
	}

	switch(target->flag){
	case R_TYPE: decomposeRTYPE(target, instruction); break;
	case I_TYPE: decomposeITYPE(target, instruction); break;
	case J_TYPE: decomposeJTYPE(target, instruction); break;
	default: break;
	}
}

void copyInstruction(char* des, char* src, int n){
	int i;
	for(i=0; i<n; i++)
		des[i] = src[i];
}

/* Decompose R Type Insturction */
void decomposeRTYPE(INSTRUCTION* target, char* instruction){
	copyInstruction(target->rs, instruction+6, REGIST_UNIT);
	copyInstruction(target->rt, instruction+11, REGIST_UNIT);
	copyInstruction(target->rd, instruction+16, REGIST_UNIT);
	copyInstruction(target->shamt, instruction+21, REGIST_UNIT);
	copyInstruction(target->funct, instruction+26, FUNCT_UNIT);
}

/* Decompose I Type Instruction */
void decomposeITYPE(INSTRUCTION* target, char* instruction){
	copyInstruction(target->rs, instruction+6, REGIST_UNIT);
	copyInstruction(target->rt, instruction+11, REGIST_UNIT);
	copyInstruction(target->immediate, instruction+16, IMMED_UNIT);
}

/* Decompose J Type Instruction */
void decomposeJTYPE(INSTRUCTION* target, char* instruction){
	copyInstruction(target->address, instruction+6, ADDRESS_UNIT);
}

/* Print Instruction */
void printInstruction(INSTRUCTION* target, int count){
	printf("inst %d: ", count);
	printInHex(target->instruction, 4, BYTE_F);
	switch(target->flag){
	case R_TYPE: printRTYPE(target); break; 
	case I_TYPE: printITYPE(target); break;
	case J_TYPE: printJTYPE(target); break;
	case WRONG_INSTRUCTION: printUnknownInstruction(); break;
	default: break;
	} 	
}

/* Print Unknown Instruction */
void printUnknownInstruction(){
	printf("unknown instruction\n");
}

/* Print Instruction Code in Hex */
void printInHex(char *instruction, int n, int code){
	unsigned int tmp;
	int i;
	
	if(code==BYTE_F){
		for(i=0; i<n; i++){
			tmp = (unsigned int)instruction[i];
			if(tmp>0x000000ff) tmp ^= 0xffffff00;
			if(tmp<0x10) printf("0%0x", tmp);
			else printf("%0x", tmp);
		}
	}
	else if(code==BIT_F){
		for(i=0; i<n; i+=4){
			tmp = instruction[i]*pow_2(3);
			tmp += instruction[i+1]*pow_2(2);
			tmp += instruction[i+2]*pow_2(1);
			tmp += instruction[i+3]*pow_2(0);
			printf("%0x", tmp);
		}
	}
	putchar(' ');	
}

void printRTYPE(INSTRUCTION* target){
	int funct, code;
	funct = BitToInt(target->funct, 6, UNSIGNED);
	
	switch(funct){
	case 32: case 33: case 34: case 35: case 36:
	case 37: case 38: case 39: case 42: case 43: code = R_DST; break;
	case 24: case 25: case 26: case 27: code = R_ST; break;
	case 8: case 17: case 19: code = R_S; break;
	case 9: code = R_DS;
	case 16: case 18: code = R_D; break;
	case 0: case 2: case 3: code = R_DTSA; break;
	case 4: case 6: case 7: code = R_DTS; break;
	case 12: code = R_SYSCALL; break;
	default: printUnknownInstruction(); return;
	}
	printRTYPEcode(target, funct, code);
}

void printRTYPEcode(INSTRUCTION* target, int funct, int code){
	int rd, rs, rt;
	int shamt;
/*
	switch(code){
	case R_SYSCALL:
		if(checkZero(target->rs, REGIST_UNIT)){
			printUnknownInstruction();
			return;
		}
	case R_S:
		if(checkZero(target->rt, REGIST_UNIT)){
			printUnknownInstruction();
			return;
		}
	case R_ST:
		if(checkZero(target->rd, REGIST_UNIT)){
			printUnknownInstruction();
			return;
		}
	case R_DST: case R_DTS:
		if(checkZero(target->shamt, REGIST_UNIT)){
			printUnknownInstruction();
			return;
		}
		break;
	case R_D:
		if(checkZero(target->rs, REGIST_UNIT)){
			printUnknownInstruction();
			return;
		}
	case R_DS:
		if(checkZero(target->shamt, REGIST_UNIT)||checkZero(target->rt, REGIST_UNIT)){
			printUnknownInstruction();
			return;
		}
		break;
	case R_DTSA:
		if(checkZero(target->rs, REGIST_UNIT)){
			printUnknownInstruction();
			return;
		}
		break;
	default: printUnknownInstruction(); return;
	}
*/			
	switch(funct){
	case 32: printf("add "); break;
	case 33: printf("addu "); break;
	case 34: printf("sub "); break;
	case 35: printf("subu "); break;
	case 36: printf("and "); break;
	case 37: printf("or "); break;
	case 38: printf("xor "); break;
	case 39: printf("nor "); break;
	case 42: printf("slt "); break;
	case 43: printf("sltu "); break;
	case 4: printf("sllv "); break;
	case 6: printf("srlv "); break;
	case 7: printf("srav "); break;
	case 24: printf("mult "); break;
	case 25: printf("multu "); break;
	case 26: printf("div "); break;
	case 27: printf("divu "); break;
	case 8: printf("jr "); break;
	case 9: printf("jalr "); break;
	case 17: printf("mthi "); break;
	case 19: printf("mtlo "); break;
	case 16: printf("mfhi "); break;
	case 18: printf("mflo "); break;
	case 12: printf("syscall\n"); return;
	case 0: printf("sll "); break;
	case 2: printf("srl "); break;
	case 3: printf("sra "); break;
	default: printUnknownInstruction(); return;
	}

	switch(code){
	case R_DTS:
	case R_DST:
		rd = BitToInt(target->rd, REGIST_UNIT, UNSIGNED);
	case R_ST:
		rt = BitToInt(target->rt, REGIST_UNIT, UNSIGNED);
	case R_S:
		rs = BitToInt(target->rs, REGIST_UNIT, UNSIGNED);
		break;
	case R_DTSA:
		rt = BitToInt(target->rt, REGIST_UNIT, UNSIGNED);
		shamt = BitToInt(target->shamt, SHAMT_UNIT, UNSIGNED);
	case R_D:
		rd = BitToInt(target->rd, REGIST_UNIT, UNSIGNED);
		break;
	case R_DS:
		rd = BitToInt(target->rd, REGIST_UNIT, UNSIGNED);
		rs = BitToInt(target->rs, REGIST_UNIT, UNSIGNED);
		break; 
	default: printUnknownInstruction(); return;
	}
	
	switch(code){
	case R_DST: printf("$%d, $%d, $%d\n", rd, rs, rt); break;
	case R_ST: printf("$%d, $%d\n", rs, rt); break;
	case R_S: printf("$%d\n", rs); break;
	case R_D: printf("$%d\n", rd); break;
	case R_DTSA: printf("$%d, $%d, %d\n", rd, rt, shamt); break;
	case R_DTS: printf("$%d, $%d, $%d\n", rd, rt, rs); break;
	case R_DS:
		if(rd == 31) printf("$%d\n", rs);
		else printf("$%d, $%d\n", rd, rs);
		break;
	default: printUnknownInstruction(); return;
	}
}

int checkZero(char* inst, int n){
	int i;
	for(i=0; i<n; i++)
		if(inst[i]!=0) break;
	if(i<n) return -1;
	return 0;
}

void printITYPE(INSTRUCTION* target){
	int  code;
	switch(target->opcode_int){
	case 8: case 9: case 10: case 11:
	case 12: case 13: case 14: code = I_TSIM; break;
	case 4: case 5: code = I_STOFF; break;
	case 32: case 33: case 35: case 36: 
	case 37: case 40: case 41: case 43: code = I_TOFFS; break;
 	case 15: code = I_TIM; break;
	default: printUnknownInstruction(); return;
	}
	printITYPEcode(target, code);	
}

void printITYPEcode(INSTRUCTION* target, int code){
	int rt, rs, imm;
	
	switch(target->opcode_int){
	case 4: printf("beq "); break;
	case 5: printf("bne "); break;
	case 8: printf("addi "); break;
	case 9: printf("addiu "); break;
	case 10: printf("slti "); break;
	case 11: printf("sltiu "); break;
	case 12: printf("andi "); break;
	case 13: printf("ori "); break;
	case 14: printf("xori "); break;
	case 15: printf("lui "); break;
	case 32: printf("lb "); break;
	case 33: printf("lh "); break;
	case 35: printf("lw "); break;
	case 36: printf("lbu "); break;
	case 37: printf("lhu "); break;
	case 40: printf("sb "); break;
	case 41: printf("sh "); break;
	case 43: printf("sw "); break;
	default: printUnknownInstruction(); return;
	}

	switch(code){
	case I_TSIM: case I_STOFF: case I_TOFFS:
		rs = BitToInt(target->rs, REGIST_UNIT, UNSIGNED);
	case I_TIM:
		rt = BitToInt(target->rt, REGIST_UNIT, UNSIGNED);
		imm = BitToInt(target->immediate, IMMED_UNIT, SIGNED);
		break;
	default: printUnknownInstruction(); return;
	}
	
	switch(code){
	case I_TSIM: printf("$%d, $%d, %d\n", rt, rs, imm); break;
	case I_STOFF: printf("$%d, $%d, %d\n", rs, rt, imm); break;
	case I_TOFFS: printf("$%d, %d($%d)\n", rt, imm, rs); break;
	case I_TIM: printf("$%d, %d\n", rt, imm); break;
	default: printUnknownInstruction(); return;
	}
}

void printJTYPE(INSTRUCTION* target){
	if(target->opcode_int==2) printf("j ");
	else if(target->opcode_int==3) printf("jal ");
	else{
		printUnknownInstruction();
		return;
	}
	printf("%d\n", BitToInt(target->address, ADDRESS_UNIT, SIGNED));
}

/* Proj2 Functions */

/* Init Registers */
void InitGeneralRegist(){
	int i, j;
	for(i=0; i<REGIST_N; i++)
		for(j=0; j<32; j++)
			generalRegisters[i].bit[j] = 0;
}
void InitPCRegist(){
	int i;
	for(i=0; i<32; i++)	pcRegister.bit[i] = 0;
	pc = 0;
}
void InitRegist(){
	InitGeneralRegist();
	InitPCRegist();
}	
/* Init Instruction Memory */
void InitInstMemory(){
	int i;
	for(i=0; i<INST_MEMORY_N; i++)
		InstructionMemory[i] = 0xFF;
}

void InitMemory(){
	InitRegist();
	InitInstMemory();
}

/* Load Instructions from File */
int LoadInstruction(FILE* fp){
	int idx, buf_l;
	int MAX_addr;
	char tmp_buf;
	MAX_addr = INST_MEMORY_N-1;
	if(fp==NULL) return FILE_ERROR;
	InitMemory();
	idx = 0;
	while(1){ 
		buf_l = fread(InstructionMemory+(idx++), sizeof(char), 1, fp);
		if(idx>MAX_addr||buf_l<1) break; 
	}
	return 0;
} 

/* Run Instructions */
int RunInstruction(int n){
	int resultCode;
	int executeCount;
	int opcode, funct;
	char TargetInst[32];
	char instName[10];
	InitRegist();
	executeCount = 0;
	while(1){
		ByteToBit(TargetInst, InstructionMemory+pc);
		pc += 4;
		updatePC();
		opcode = interpretInst(TargetInst, &funct);
		resultCode = runInst(TargetInst, opcode, funct);
		executeCount++;
		if(resultCode||executeCount>n){
			printf("unknown instruction\n");
			printf("Executed %d instructions\n", executeCount);
			break;
		}
		else if(executeCount>=n){
			printf("Executed %d instructions\n", executeCount);
			break;
		}
	}
	return 0;
}

void updatePC(){
	int i;
	unsigned int tmp;
	tmp = pc;
	for(i = REGIST_N-1; i>=0; i--){
		pcRegister.bit[i] = tmp%2;
		tmp /= 2;
	}
}

int interpretInst(char* inst, int* funct){
	int opcode;
	opcode = BitToInt(inst, OPCODE_UNIT, UNSIGNED);
	if(opcode==0) *funct = BitToInt(inst+26, FUNCT_UNIT, UNSIGNED);
	else *funct = -1;
	return opcode;
}	

int runInst(char* inst, int opcode, int funct){
	switch(opcode){
	case 0: return runRTYPE(inst, funct);
	case 8: case 9: case 10: case 11: case 12:
	case 13: case 14: case 15: return runITYPE(inst, opcode);
	default: return -1;
	}
	return -1;
}

void shiftLogic(int des, int src, int shamt, char to){
	int i, j;
	switch(to){
	case 'L':
	for(i=0, j=shamt; j<REGIST_N; i++, j++)
		generalRegisters[des].bit[i] = generalRegisters[src].bit[j];
	for(i=REGIST_N-shamt; i<REGIST_N; i++)
		generalRegisters[des].bit[i] = 0;
	break;
	case 'R':
	for(i=REGIST_N-1, j=REGIST_N-1-shamt; j>=0; i--, j--)
		generalRegisters[des].bit[i] = generalRegisters[src].bit[j];
	for(i=0; i<shamt; i++)
		generalRegisters[des].bit[i] = 0;
	}	
}

void shiftArith(int des, int src, int shamt, char to){
	int i, j;
	char ext;
	switch(to){
	// case 'L':
	// for(i=0, j=shamt; j<REGIST_N; i++, j++)
	// 	generalRegisters[des].bit[i] = generalRegisters[src].bit[j];
	// for(i=REGIST_N-shamt; i<REGIST_N; i++)
	// 	generalRegisters[des].bit[i] = 0;
	// break;
	case 'R':
	ext = generalRegisters[src].bit[0];
	for(i=REGIST_N-1, j=REGIST_N-1-shamt; j>=0; i--, j--)
		generalRegisters[des].bit[i] = generalRegisters[src].bit[j];
	for(i=0; i<shamt; i++)
		generalRegisters[des].bit[i] = ext;
	break;
	}	
}

int runRTYPE(char* inst, int funct){
	int rd, rs, rt, shamt;
	int i, j;
	rs = BitToInt(inst+6, REGIST_UNIT, UNSIGNED);
	rt = BitToInt(inst+11, REGIST_UNIT, UNSIGNED);
	rd = BitToInt(inst+16, REGIST_UNIT, UNSIGNED);
	shamt = BitToInt(inst+21, SHAMT_UNIT, UNSIGNED);
	switch(funct){
	case 0: //sll
		//if(rs!=0||rd==0) return -1;
		shiftLogic(rd, rt, shamt, 'L');
		break;
	case 2: //srl
		//if(rs!=0||rd==0) return -1;
		shiftLogic(rd, rt, shamt, 'R');
		break;
	case 3: //sra
		//if(rs!=0||rd==0) return -1;
		shiftArith(rd, rt, shamt, 'R');
		break;
	case 4: //sllv
		//if(shamt!=0||rd==0) return -1;
		shamt = BitToInt(generalRegisters[rs].bit+(REGIST_N-REGIST_UNIT), REGIST_UNIT, UNSIGNED);
		shiftLogic(rd, rt, shamt, 'L');
		break;
	case 6: //srlv
		//if(shamt!=0||rd==0) return -1;
		shamt = BitToInt(generalRegisters[rs].bit+(REGIST_N-REGIST_UNIT), REGIST_UNIT, UNSIGNED);
		shiftLogic(rd, rt, shamt, 'R');
		break;
	case 7: //srav
		//if(shamt!=0||rd==0) return -1;
		shamt = BitToInt(generalRegisters[rs].bit+(REGIST_N-REGIST_UNIT), REGIST_UNIT, UNSIGNED);
		shiftArith(rd, rt, shamt, 'R');
		break;
	case 32: case 33://add, addu
		//if(shamt!=0||rd==0) return -1;
		add(rd, rs, rt);
		break;
	case 34: case 35: //sub, subu
		//if(shamt!=0||rd==0) return -1;
		sub(rd, rs, rt);
		break;
	case 36: //and
		//if(shamt!=0||rd==0) return -1;
		for(i=0; i<REGIST_N; i++)
			generalRegisters[rd].bit[i] = generalRegisters[rs].bit[i]&&generalRegisters[rt].bit[i];
		break;
	case 37: //or
		//if(shamt!=0||rd==0) return -1;
		for(i=0; i<REGIST_N; i++)
			generalRegisters[rd].bit[i] = generalRegisters[rs].bit[i]||generalRegisters[rt].bit[i];
		break;
	case 38: //xor
		//if(shamt!=0||rd==0) return -1;
		for(i=0; i<REGIST_N; i++)
			generalRegisters[rd].bit[i] = generalRegisters[rs].bit[i]==1 ? (generalRegisters[rt].bit[i]==1 ? 0 : 1) : (generalRegisters[rt].bit[i]==1 ? 1 : 0);
		break;
	case 39: //nor
		//if(shamt!=0||rd==0) return -1;
		for(i=0; i<REGIST_N; i++)
			if(generalRegisters[rs].bit[i]==0&&generalRegisters[rt].bit[i]==0)
				generalRegisters[rd].bit[i] = 1;
			else generalRegisters[rd].bit[i] = 0;
		break;
	case 42: //slt
		//if(shamt!=0||rd==0) return -1;
		slt(rd, rs, rt, SIGNED);
		break;
	case 43: //sltu
		//if(shamt!=0||rd==0) return -1;
		slt(rd, rs, rt, UNSIGNED);
		break;
	default: return -1;
	}
	return 0;
}

void slt(int rd, int rs, int rt, int code){
	int rs_n, rt_n;
	unsigned int rs_nu, rt_nu;
	int i;
	switch(code){
	case SIGNED:
		rs_n = BitToInt(generalRegisters[rs].bit, REGIST_N, SIGNED);
		rt_n = BitToInt(generalRegisters[rt].bit, REGIST_N, SIGNED);
		if(rs_n<rt_n) generalRegisters[rd].bit[REGIST_N-1] = 1;
		else generalRegisters[rd].bit[REGIST_N-1] = 0;	
		break;
	case UNSIGNED:
		rs_nu = BitToInt(generalRegisters[rs].bit, REGIST_N, UNSIGNED);
		rt_nu = BitToInt(generalRegisters[rt].bit, REGIST_N, UNSIGNED);
		if(rs_nu<rt_nu) generalRegisters[rd].bit[REGIST_N-1] = 1;
		else generalRegisters[rd].bit[REGIST_N-1] = 0;
		break;
	}
	for(i=0; i<REGIST_N-1; i++) generalRegisters[rd].bit[i] = 0;
}

void add(int rd, int rs, int rt){
	char c, tmp;
	int i;
	c = 0;
	for(i=REGIST_N-1; i>=0; i--){
		tmp = generalRegisters[rs].bit[i] + generalRegisters[rt].bit[i] + c;
		c = tmp/2;
		tmp %= 2;
		generalRegisters[rd].bit[i] = tmp;
	}
}

void sub(int rd, int rs, int rt){
	unsigned int a, b, result;
	int i;

	a = BitToInt(generalRegisters[rs].bit, REGIST_N, UNSIGNED);
	b = BitToInt(generalRegisters[rt].bit, REGIST_N, UNSIGNED);
	result = a-b;
	for(i=REGIST_N-1; i>=0; i--){
		generalRegisters[rd].bit[i] = result%2;
		result /= 2;
	}
}

int runITYPE(char* inst, int opcode){
	int rt, rs, imm;
	int i;
	rs = BitToInt(inst+6, REGIST_UNIT, UNSIGNED);
	rt = BitToInt(inst+11, REGIST_UNIT, UNSIGNED);
	imm = BitToInt(inst+16, IMMED_UNIT, SIGNED);
	switch(opcode){
	case 8: case 9: //addi, addiu
		//if(rt==0) return -1;
		addi(rt, rs, imm);
		break;
	case 10: //slti
		//if(rt==0) return -1;
		slti(rt, rs, inst, SIGNED);
		break;
	case 11: //sltiu
		//if(rt==0) return -1;
		slti(rt, rs, inst, UNSIGNED);
		break;
	case 12: //andi
		//if(rt==0) return -1;
		for(i=16; i<REGIST_N; i++)
			generalRegisters[rt].bit[i] = generalRegisters[rs].bit[i]==1&&inst[i]==1;
		for(i=0; i<16; i++) generalRegisters[rt].bit[i] = 0;
		break;
	case 13: //ori
		//if(rt==0) return -1;
		for(i=16; i<REGIST_N; i++)
			generalRegisters[rt].bit[i] = generalRegisters[rs].bit[i]==1||inst[i]==1;
		for(i=0; i<16; i++) generalRegisters[rt].bit[i] = generalRegisters[rs].bit[i];
 		break;
	case 14: //xori
		//if(rt==0) return -1;
		for(i=16; i<REGIST_N; i++)
			generalRegisters[rt].bit[i] = generalRegisters[rs].bit[i]==1 ? (inst[i]==1 ? 0 : 1) : (inst[i]==1 ? 1 : 0);
		for(i=0; i<16; i++) generalRegisters[rt].bit[i] = generalRegisters[rs].bit[i];
		break;
	case 15: //lui
		//if(rt==0) return -1;
		for(i=0; i<16; i++)	generalRegisters[rt].bit[i] = inst[i+16];
		for(i=16; i<REGIST_N; i++) generalRegisters[rt].bit[i] = 0;
		break;
	default: return -1;
	}
	return 0;
}

void slti(int rt, int rs, char* inst, int code){
	int i;
	int rs_n, imm;
	unsigned int rs_nu, imm_nu;
	char immediate[REGIST_N];

	for(i=16; i<REGIST_N; i++) immediate[i] = inst[i];
	if(immediate[16]==0) for(i=0; i<16; i++) immediate[i] = 0;
	else for(i=0; i<16; i++) immediate[i] = 1;

	switch(code){
	case SIGNED:
		rs_n = BitToInt(generalRegisters[rs].bit, REGIST_N, SIGNED);
		imm = BitToInt(immediate, REGIST_N, SIGNED);
		if(rs_n<imm) generalRegisters[rt].bit[REGIST_N-1] = 1;
		else generalRegisters[rt].bit[REGIST_N-1] = 0;
		break;
	case UNSIGNED:
		rs_nu = BitToInt(generalRegisters[rs].bit, REGIST_N, UNSIGNED);
		imm_nu = BitToInt(immediate, REGIST_N, UNSIGNED);
		if(rs_nu<imm_nu) generalRegisters[rt].bit[REGIST_N-1] = 1;
		else generalRegisters[rt].bit[REGIST_N-1] = 0;
		break;
	}
	for(i = 0; i<REGIST_N-1; i++) generalRegisters[rt].bit[i] = 0;
}

void addi(int rt, int rs, int imm){
	int rs_n, result, flag;	
	int i, c, tmp;
	rs_n = BitToInt(generalRegisters[rs].bit, 32, SIGNED);
	result = rs_n + imm;
	if(result>=0) flag = 0;
	else{
		result *= -1;
		flag = 1;
	}
	for(i=REGIST_N-1; i>=0; i--){
		generalRegisters[rt].bit[i] = result%2;
		result /=2;
	}
	if(flag){
		c = 1;
		for(i=0; i<REGIST_N; i++)
			if(generalRegisters[rt].bit[i]==0) generalRegisters[rt].bit[i] = 1;
			else generalRegisters[rt].bit[i] = 0;
		
		for(i=REGIST_N-1; i>=0; i--){
			tmp = generalRegisters[rt].bit[i] + c;
			c = tmp/2;
			generalRegisters[rt].bit[i] = tmp%2;
		}
	}
}
