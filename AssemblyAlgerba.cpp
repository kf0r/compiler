#include "./LowBlock.hpp"

void LowLevelProgram::generateMult(){
    LowLevelBlock* multBlock = new LowLevelBlock();
    arch->setBlock(multBlock);

/*00*/    arch->get(B);
/*01*/    arch->jzero(true);              //JZERO 18
/*02*/    arch->get(C);
/*03*/    arch->rst(F);                   //RST f
/*04*/    arch->jzero(true);              //JZERO 18
/*05*/    arch->put(G);                   //PUT g
/*06*/    arch->shr(G);                   //SHR g
/*07*/    arch->shl(G);                   //SHL g
/*08*/    arch->sub(G);                   //SUB g
/*09*/    arch->jzero(true);              //JZERO 13
/*10*/    arch->get(F);                   //GET f 
/*11*/    arch->add(B);                   //ADD b
/*12*/    arch->put(F);                   //PUT f
/*13*/    arch->shl(B);                   //SHL b 
/*14*/    arch->shr(C);                   //SHR c
/*15*/    arch->get(C);                   //GET c
/*16*/    arch->jpos(true);               //JZERO 10
/*17*/    arch->get(F);                   //GET f 
/*18*/    arch->inc(H);
/*19*/    arch->inc(H);
/*20*/    arch->jumpr(H);

    dynamic_cast<JZero*>(multBlock->instr[1])->jumpTo=multBlock->instr[18];
    dynamic_cast<JZero*>(multBlock->instr[4])->jumpTo=multBlock->instr[18];
    dynamic_cast<JZero*>(multBlock->instr[9])->jumpTo=multBlock->instr[13];
    dynamic_cast<JPos*>(multBlock->instr[16])->jumpTo=multBlock->instr[10];

    proceduresBlock.insert(std::pair<std::string, LowLevelBlock*> ("*", multBlock));
}

void LowLevelProgram::generateDiv(){
    LowLevelBlock* divBlock = new LowLevelBlock();
    arch->setBlock(divBlock);
/*00*/    arch->get(C);
/*01*/    arch->jpos(true); //JPOS 05
/*02*/    arch->put(G);
/*03*/    arch->put(B);
/*04*/    arch->jump("");   // JUMP 34
/*05*/    arch->put(E);     //continue
/*06*/    arch->rst(G);
/*07*/    arch->rst(D);
/*08*/    arch->rst(F);
/*09*/    arch->get(C); //
/*10*/    arch->sub(B);
/*11*/    arch->jpos(true); //JPOS 15
/*12*/    arch->shl(C); //
/*13*/    arch->inc(D);
/*14*/    arch->jump("");   //JUMP 09
/*15*/    arch->get(D);  
/*16*/    arch->rst(D);
/*17*/    arch->jzero(true); //JZERO 34
/*18*/    arch->rst(F); 
/*19*/    arch->inc(F);
/*20*/    arch->shl(F);
/*21*/    arch->dec(A);
/*22*/    arch->jpos(true); //JPOS 20
/*23*/    arch->shr(F);
/*24*/    arch->get(G);
/*25*/    arch->add(F);
/*26*/    arch->put(G);
/*27*/    arch->shr(C);
/*28*/    arch->get(B);
/*29*/    arch->sub(C);
/*30*/    arch->put(B);
/*31*/    arch->get(E);
/*32*/    arch->put(C);
/*33*/    arch->jump("");  //jump 09
/*34*/    arch->inc(H);
/*35*/    arch->inc(H);
/*36*/    arch->jumpr(H);
    dynamic_cast<JPos*>(divBlock->instr[1])->jumpTo=divBlock->instr[5];
    dynamic_cast<Jump*>(divBlock->instr[4])->jumpTo=divBlock->instr[34];
    dynamic_cast<JPos*>(divBlock->instr[11])->jumpTo=divBlock->instr[15];
    dynamic_cast<Jump*>(divBlock->instr[14])->jumpTo=divBlock->instr[9];
    dynamic_cast<JZero*>(divBlock->instr[17])->jumpTo=divBlock->instr[34];
    dynamic_cast<JPos*>(divBlock->instr[22])->jumpTo=divBlock->instr[20];
    dynamic_cast<Jump*>(divBlock->instr[33])->jumpTo=divBlock->instr[9];

    proceduresBlock.insert(std::pair<std::string, LowLevelBlock*> ("/", divBlock));
}