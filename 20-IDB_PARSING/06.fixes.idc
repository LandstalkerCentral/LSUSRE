
/*
 *  FIXES SCRIPT 
 *  This script will contain all instruction for fixes
 *  on the IDB after the main IDC script has been applied.
 *
 *
 *  TABLE FIXES :
 *  IDA's IDC export function does not properly export 
 *  the following structures, when they
 *  are located after address 0xFFFF :
 *  - Relative Jump Tables (RJT, labeled with prefix "rjt_")
 *  - Branch Tables (BT, labeled with prefix "bt_")
 *  - Relative Pointer Tables (RPT, labeled with prefix "rpt_")
 *  This script contains the needed instructions to 
 *  fix all the RJTs/BTs/RPTs that are defined in the IDB. 
 *  Beware :
 *  Everytime a new RJT/BT/RPT is defined after 0xFFFF, 
 *  it also has    to be defined in this script.
 *
 *  
 *  INSTRUCTION FIXES :
 *  Some instructions are not properly represented by IDA.
 *  Details in more comments below.
 *
 */

#include <idc.idc>

static main(void) {

    Message("FIXING...\n");

    Message("Relative Jump Tables...");
    fixRJTs();
    Message(" DONE.\nRelative Pointer Tables...");        
    fixRPTs();
    Message(" DONE.\nInstruction Representations...");            
    fixInstructionRepresentations();
    Message(" DONE.\nSingle Instructions...");        
    fixSingleInstructions();
    Message(" DONE.\nROM Expand Tweaks...");        
    insertRomExpandTweaks();
    Message(" DONE.\n");
    
    Message("END OF FIXES.\n");
    Batch(0);

}

static fixRJTs() {
    makeRjt(0x28D9C,0x28DAC);
    makeRjt(0x28EB2,0x28EBA);
    //makeRjt(0x2A49A,0x2A4AA);
}

static fixRPTs() {
    /* example
    makeRpt(0x47A88,0x47AE8);
    */
}


/*
 *  IDC SCRIPT : FIX INSTRUCTION REPRESENSATIONS
 *
 *  It is known that IDA's mc68 module doesn't
 *  properly output certain instructions with 
 *  specific addressing modes. 
 *
 *  This script helps to fix these 
 *  instructions :  
 *  move.l a6,usp were displayed as move a6,usp.
 *  jsr (loc).w were displayed as jsr loc.
 *  jsr loc(pc) were displayed as jsr loc.
 *  jmp (loc).w were displayed as jmp loc.
 *  jmp loc(pc) were displayed as jmp loc.  
 *  lea loc(pc),a0 were displayed as lea loc, a0.
 *  lea loc(pc),a1 were displayed as lea loc, a1. 
 *  lea loc(pc),a2 were displayed as lea loc, a2. 
 *  lea loc(pc),a3 were displayed as lea loc, a3. 
 *  lea loc(pc),a4 were displayed as lea loc, a4. 
 *  lea loc(pc),a5 were displayed as lea loc, a5. 
 *  lea loc(pc),a6 were displayed as lea loc, a6. 
 *  lea loc(pc),a7 were displayed as lea loc, a7.
 *
 *  It finds every instructions 
 *  in formatted code and asks for each one
 *  of them if you want it to be properly formatted.
 *
 *  "No" skips the instruction.
 *  "Cancel" stops the script.
 *
 *  Be aware that it will only find instructions if they have been formatted as code. 
 *  They won't be identified if they are still known as pure data. 
 *
 */
static fixInstructionRepresentations(){
    
    auto batch;
    
    Batch(0);
    //batch = AskYN(1,"Fix Instruction Represensations : BATCH MODE ?");
    //if (batch==-1) return;
    //Batch(batch);
    
    fix("4E 66","move.l  a6,usp","move a6,usp","move.l a6,usp");
    
    fix("4E B8","jsr     (%s).w","jsr loc","jsr (loc).w");
    fix("4E BA","jsr     %s(pc)","jsr loc","jsr loc(pc)");
    fix("4E F8","jmp     (%s).w","jmp loc","jmp (loc).w");
    fix("4E FA","jmp     %s(pc)","jmp loc","jmp loc(pc)");
    
    fix("41 FA","lea     %s(pc), a0","lea loc, a0","lea loc(pc),a0");
    fix("43 FA","lea     %s(pc), a1","lea loc, a1","lea loc(pc),a1");
    fix("45 FA","lea     %s(pc), a2","lea loc, a2","lea loc(pc),a2");
    fix("47 FA","lea     %s(pc), a3","lea loc, a3","lea loc(pc),a3");
    fix("49 FA","lea     %s(pc), a4","lea loc, a4","lea loc(pc),a4");
    fix("4B FA","lea     %s(pc), a5","lea loc, a5","lea loc(pc),a5");
    fix("4D FA","lea     %s(pc), a6","lea loc, a6","lea loc(pc),a6");
    fix("4F FA","lea     %s(pc), a7","lea loc, a7","lea loc(pc),a7");
    
    // New Landstalker-specific instruction improperly represented by IDA.
    
    fix("30 3A","move.w     %s(pc), d0","move.w loc, d0","move.w (loc).w,d0");
    fix("32 3A","move.w     %s(pc), d1","move.w loc, d1","move.w (loc).w,d1");
    
    fix("23 FA","move.l     %s(pc), %s","move.l loc1, (loc2).l","move.l (loc1).w,(loc2).l");
    fix("33 FA","move.w     %s(pc), %s","move.w loc1, (loc2).l","move.w (loc1).w,(loc2).l");
    

}

/*
 *      fixSingleInstructions()
 *
 *  Add a line to this function for every specific instruction that
 *  needs to be changed with its own individual logic.
 *
 *  For example, here we use OpHex commands to change falsely
 *  identified offsets into just hex values, so IDA doesn't create
 *  false xrefs and names.
 *
 */
 
static fixSingleInstructions(){

    /* Operators being interpreted as offsets wrongly */
    /* examples 
    OpHex(0x128C0,1);
    MakeNameEx(0xFC,"",0);
    */
    
    /* Change sign of operands */
    //OpSign(0x11BC,0);
    
    /* Convert operands to symbolic constants */
    /* examples
    OpEnum(0x9B96,1,GetEnum("Battle_Cutscene"));
    SetManualInsn(0x1A4,"declareRomEnd"); 
    */
    
    /* Code parsing blocked by false offset recognition */
    
    MakeUnkn(0x1C80,DOUNK_SIMPLE);
    MakeCode(0x1C7E);
    SetFunctionEnd(0x1C78,0x1D06);
    
    MakeDword(0xE80E);
    MakeDword(0xE812);
    MakeDword(0xE816);
    MakeDword(0xE81A);
    MakeDword(0xE81E);
    MakeDword(0xE822);
    MakeDword(0xE826);
    MakeDword(0xE82A);
    MakeDword(0xE82E);
    OpHex(0xE80E,0);
    OpHex(0xE812,0);
    OpHex(0xE816,0);
    OpHex(0xE81A,0);
    OpHex(0xE81E,0);
    OpHex(0xE822,0);
    OpHex(0xE826,0);
    OpHex(0xE82A,0);
    OpHex(0xE82E,0);

}

static insertRomExpandTweaks(){
    auto ea;
    
    /* Illegal operand values */
    SetManualInsn(0xDEE,"movep.w d0,-3(a6)");
    SetManualInsn(0xDFC,"movep.w d0,-3(a6)");

    /* Align directives being not permissive enough 
    to remove data chunks for ROM expansion */
    SetManualInsn(0x01008C,"align $010300");
    SetManualInsn(0x019314,"align $019514");
    SetManualInsn(0x022E50,"align $022E80");
    SetManualInsn(0x03838C,"align $038600");
    SetManualInsn(0x043E70,"align $044010");
    SetManualInsn(0x09AC6C,"align $09B000");
    SetManualInsn(0x0A08AC,"align $0A0A00");
    SetManualInsn(0x11F314,"align $120000");
    SetManualInsn(0x1A42DE,"align $1A4400");
    SetManualInsn(0x1AF5FA,"align $1AF800");
    SetManualInsn(0x1DF9F8,"align $1E0000");
    
    
    /* Conditional manual instructions when implied by moved data */
    /* examples
    SetManualInsn(0x477A8,"conditionalPc lea,MapSetups,a1");
    SetManualInsn(0x54CAA,"conditionalBsr sub_4F48A");
    SetManualInsn(0x427C,"conditionalWordAddr lea,BattleMapCoordinates,a0");
    */
    


}

static fix(pattern, manualInstruction, wrongInstString, newInstString){

    auto addr; // current location
    auto opnd; // operand found at current location
    auto secondopnd; // operand found at current location
    auto action; // action asked to user
    auto rep; // proper representation of instruction
    action = 1;
    
    // Start search from current address on screen
    for(addr=0;addr!=BADADDR;addr=FindBinary(addr+1,7,pattern)){
        opnd = GetOpnd(addr,0);
        secondopnd = GetOpnd(addr,1);
        if (opnd!=""){
            if(secondopnd!=""){
                rep = form(manualInstruction,opnd,secondopnd);
                //Jump(addr);
                //action = AskYN(1,form("Change representation from %s to %s ?",wrongInstString, newInstString));
                if (action==-1) break;
                if (action==1){
                    //Message(form("\n0x%d : %s changed to %s",addr,wrongInstString, newInstString));
                    SetManualInsn(addr,rep);
                }
                else{
                    //Message(form("\n0x%d : %s NOT changed to %s",addr,wrongInstString, newInstString));
                }
            }else{
                rep = form(manualInstruction,opnd);
                //Jump(addr);
                //action = AskYN(1,form("Change representation from %s to %s ?",wrongInstString, newInstString));
                if (action==-1) break;
                if (action==1){
                    //Message(form("\n0x%d : %s changed to %s",addr,wrongInstString, newInstString));
                    SetManualInsn(addr,rep);
                }
                else{
                    //Message(form("\n0x%d : %s NOT changed to %s",addr,wrongInstString, newInstString));
                }
            }
        }
    }
}

static makeRpt(base, end){
    auto addr;
    addr = base;
    while(addr < end){
        //Jump(addr);
        MakeData(addr, FF_WORD, 0x2, 0);
        if(Word(addr) > 0x8000) {
            OpOffEx(addr, -1, REF_LOW16, base + (Word(addr)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(addr, -1, REF_OFF32, -1, base, 0);
        }
        addr = addr+2;
    }
}

static makeRjt(base, end){
    auto addr;
    addr = base;
    while(addr < end){
        //Jump(addr);
        MakeData(addr, FF_WORD, 0x2, 0);
        if(Word(addr) > 0x8000) {
            OpOffEx(addr, -1, REF_LOW16, base + (Word(addr)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(addr, -1, REF_OFF32, -1, base, 0);
        }
        addr = addr+2;
    }
}

static makeRjtWithOneWordBetweenEachEntry(base, end){
    auto addr;
    addr = base;
    while(addr < end){
        //Jump(addr);
        MakeData(addr, FF_WORD, 0x2, 0);
        addr = addr+2;
        MakeData(addr, FF_WORD, 0x2, 0);
        if(Word(addr) > 0x8000) {
            OpOffEx(addr, -1, REF_LOW16, base + (Word(addr)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(addr, -1, REF_OFF32, -1, base, 0);
        }
        addr = addr+2;
    }
}



static makeRelativeOffset(ea,base){
        if(Word(ea) > 0x8000) {
            OpOffEx(ea, -1, REF_LOW16, base + (Word(ea)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(ea, -1, REF_OFF32, -1, base, 0);
        }
}