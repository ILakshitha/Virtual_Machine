MEM_SIZE=100;

reg={'a':0, 'b':0, 'c':0, 'd':0, 'e':0,'f':0,'sp':0,'acc':0, 'pc':0, 'ivec':0, 'int':0, 'timer':0, 'halt':False};

memory=[0]*MEM_SIZE;

def mov(opr): #.. move a value of a register to another register
	reg[opr[0]]=reg[opr[1]];
	reg['pc']=reg['pc']+1;

def movv(opr): #.. copy a value to a register
	reg[opr[0]]=int(opr[1]);
	reg['pc']=reg['pc']+1;

def load(opr): #.. load a value in a memory loaction to a given register
	reg[opr[0]]=memory[int(opr[1])];
	reg['pc']=reg['pc']+1;

def loadr(opr): #.. load a value in a memory location pointed by a register to a given register
	reg[opr[0]]=memory[reg[opr[1]]];
	reg['pc']=reg['pc']+1;

def store(opr): #.. store a value of a register in memory
	memory[int(opr[0])]=reg[opr[1]];
	reg['pc']=reg['pc']+1;

def storer(opr): #.. store a value of a register in a memory location pointed by a register
	memory[reg[opr[0]]]=reg[opr[1]];
	reg['pc']=reg['pc']+1;

def add(opr): #.. add values of two registers
	reg['acc']=reg[opr[0]]+reg[opr[1]];
	reg['pc']=reg['pc']+1;

def sub(opr): #.. substract values of two registers
	reg['acc']=reg[opr[0]]-reg[opr[1]];
	reg['pc']=reg['pc']+1;

def mod(opr): #.. modulus values of two registers
	reg['acc']=reg[opr[0]] % reg[opr[1]];
	reg['pc']=reg['pc']+1;

def call(opr): #.. execute function stored in another location
	reg['sp']=reg['sp']+1;
	memory[reg['sp']]=reg['pc']+1;
	reg['pc']=int(opr[0]);

def ret(opr): #.. return to function called location
	reg['pc']=memory[reg['sp']];
	reg['sp']=reg['sp']-1;

def out(opr): #.. display the value of a register
	print(reg[opr[0]]);
	reg['pc']=reg['pc']+1;

def push(opr): #.. push a value of a register to stack
	reg['sp']=reg['sp']+1;
	memory[reg['sp']]=reg[opr[0]];
	reg['pc']=reg['pc']+1;

def pop(opr): #.. push a value from the stack
	reg[opr[0]]=memory[reg['sp']];
	reg['sp']=reg['sp']-1;
	reg['pc']=reg['pc']+1;

def jmp(opr): #.. point the next instruction to a given instruction
	reg['pc']=int(opr[0]);

def jnz(opr): #.. point PC to a given value when the value of given register is not equal to 0
	if reg[opr[1]]!=0:
		reg['pc']=int(opr[0]);
	else:
		reg['pc']=reg['pc']+1;

def halt(opr): #.. hault the program
	reg['halt']=True;
	reg['pc']=reg['pc']+1;


f=open('prog.asm','r');

def runm():
	while reg['halt']==False:
		i=reg['pc'];
		op=globals()[memory[i][0]];
		# print(i),
		# print(memory[i][0:]) ;
		op(memory[i][1:]);
		pass;
	
		reg['timer']=reg['timer']-1;
		if reg['int']==1 and reg['timer']==0:
			reg['sp']=reg['sp']+1;
			memory[reg['sp']]=reg['pc'];
			reg['pc']=reg['ivec'];
			reg['int']=0;
	
for l in f:
	if l.startswith("#"):
		continue;

	comm= l.split();
	if comm:
		memory[int(comm[0])] = comm[1:];

f.close()
	
runm();
	
print(reg);
print(memory);
