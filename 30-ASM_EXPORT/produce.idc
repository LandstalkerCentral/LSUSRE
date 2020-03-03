
/*
 *  Attempt at producing ASM file from IDC script 
 *  instead of IDA's function, for more flexibility.
 */

#include <idc.idc>

static main(void) {

    Message("PRODUCING ASM...\n");

    produceEnums();
    produceConst();
    produceMain();
    
    Message("\nEND OF ASM PRODUCTION.\n");

}

static produceLayoutFile(){

    auto file;
    file = fopen("disasm\\layout\\ls-00-romlayout.asm","w");
    
    writestr(file,"\n; ROM LAYOUT FILE\n;\n; Original ROM layout results in a 2MB ROM.\n; Sections can be moved to get more free space by changing declaration order and by using align directives to pad section ends until desired end offset.");
    writestr(file,"\n; (beware : ROMs over 2MB imply to manage SRAM bankswitching first)");
    writestr(file,"\n\n");

    produceSectionOne(file,    "01", 0x000000, 0x010300, 0x010300-0x01008C, "0x000000..0x010300 : Technical Layer, Initialization, Low Level Game Engine");
    produceGenericSection(file,"02", 0x010300, 0x019514, 0x019514-0x019314, "0x010300..0x019514 : To figure out and describe succinctly");
    produceGenericSection(file,"03", 0x019514, 0x022E80, 0x022E80-0x022E50, "0x019514..0x022E80 : To figure out and describe succinctly");
    produceGenericSection(file,"04", 0x022E80, 0x038600, 0x038600-0x03838C, "0x022E80..0x038600 : To figure out and describe succinctly");
    produceGenericSection(file,"05", 0x038600, 0x044010, 0x044010-0x043E70, "0x038600..0x044010 : To figure out and describe succinctly");
    produceSectionSix(file,    "06", 0x044010, 0x09B000, 0x09B000-0x09AC6C, "0x044010..0x09B000 : Map Tilesets, Intro Font");
    produceGenericSection(file,"07", 0x09B000, 0x0A0A00, 0x0A0A00-0x0A08AC, "0x09B000..0x0A0A00 : To figure out and describe succinctly");
    produceSectionEight(file,  "08", 0x0A0A00, 0x120000, 0x120000-0x11F314, "0x0A0A00..0x120000 : Map data, region check");
    produceSectionNine(file,   "09", 0x120000, 0x1A4400, 0x1A4400-0x1A42DE, "0x120000..0x1A4400 : Sprite data");
    produceSectionTen(file,    "10", 0x1A4400, 0x1AF800, 0x1AF800-0x1AF5FA, "0x1A4400..0x1AF800 : Code to figure out, Sprite Palettes");
    produceSectionEleven(file, "11", 0x1AF800, 0x1E0000, 0x1E0000-0x1DF9F8, "0x1AF800..0x1E0000 : Map Blocks");
    produceGenericSection(file,"12", 0x1E0000, 0x200000, 0x200000-0x1E0000, "0x1E0000..0x1F6000 : PCM Bank 0, PCM Bank 1, Music bank 0, Sound driver, Music Bank 1.");
    // Expanded 4MB layout to implement later
    //writestr(file,"                conditionalRomExpand    ; if EXPANDED_ROM = 1, then include next layout file to fill the ROM up to 0x3FFFFF");

    fclose(file);

}

static produceEnums(){
    auto i,j,enumQty,id,enumName,bmask,enumCount,constant,constId,output,file;
    file = fopen("disasm\\lsenums.asm","w");
    Message("\nWriting Enums to lsenums.asm ...");
    enumQty = GetEnumQty();
    for(i=0;i<enumQty;i++){
        id = GetnEnum(i);
        enumName = GetEnumName(id);
        //Message("\n\n; ---------------------------------------------------------------------------\n");
        writestr(file,"\n\n; ---------------------------------------------------------------------------\n");
        //Message(form("\n; enum %s",enumName));
        bmask = GetFirstBmask(id);
        if(bmask==-1){writestr(file,form("\n; enum %s",enumName));}
        else{writestr(file,form("\n; enum %s (bitfield)",enumName));}
        // Iterate bitmasks
        while(bmask!=0){
            enumCount = GetEnumSize(id);
            constant = GetFirstConst(id,bmask);
            // Iterate constants
            while(enumCount>0){
                j=0;
                constId = GetConstEx(id,constant,j,bmask);
                while(constId != -1){
                    output = form("\n%s: equ $%s",GetConstName(constId),ltoa(constant,16));
                    //Message(output);
                    writestr(file,output);
                    j++;
                    constId = GetConstEx(id,constant,j,bmask);
                }
                constant = GetNextConst(id,constant,bmask);
                enumCount--;
            }
            // Break out of loop after iterating last bitmask
            if(bmask==-1){break;}
            bmask = GetNextBmask(id,bmask);
        }
    }
    fclose(file);
    Message("DONE.");
}

static formEnumMember(constName,constant) {
    auto enumMember;
    enumMember = formEnumMemberEx(constName,constant,0);
    return enumMember;
}

static formEnumMemberWithHex(constName,constant) {
    auto enumMember;
    enumMember = formEnumMemberEx(constName,constant,1);
    return enumMember;
}

static formEnumMemberEx(constName,constant,hex) {
    auto operand,enumMember;
    if(hex==1){operand = "$";}
    else{operand = "";}
    enumMember = form("%s: equ %s%s", constName, operand, constant);
    return enumMember;
}

static produceConst(void) {
    auto seg,end,ea,segName,name,file;
    Message("\nWriting offset constants to lsconst.asm ...");
    file = fopen("disasm\\lsconst.asm","w");
    writestr(file,"; LSCONST.ASM INCLUDED AT START OF LS.ASM\n\n");
    seg = FirstSeg();
    seg = NextSeg(seg);
    while(seg != BADADDR){
        end = SegEnd(seg);
        segName = SegName(seg);
        writestr(file,form("; START OF SEGMENT %s OFFSETS FROM %a TO %a\n",segName, seg, end));
        ea = seg;
        while(ea<end){
            name = GetTrueName(ea);
            if(name!=""){
                writestr(file,form("%s: equ $%s\n",name,ltoa(ea,16)));
            }
            ea = ea + ItemSize(ea);
        }
        writestr(file,form("; END OF SEGMENT %s OFFSETS FROM %a TO %a\n\n",segName, seg, end));
        seg = NextSeg(seg);
    }
    fclose(file);
    Message("DONE.\n");
}


static produceMain(){

    auto seg,end,ea,itemSize,action,currentLine,previousLine,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    Message("Writing main assembly file to ls.asm ...");    
    action = 1;
    file = fopen("disasm\\ls.asm","w");
    writeHeader(file);

    produceLayoutFile();

    fclose(file);
    Message("\nDONE.");    
}





static produceSectionOne(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\ls-%s-0x00000%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\romheader",0x0,0x200,"ROM header");
    produceAsmSection(file,"",0x200,0x4B8);
    produceAsmScript(file,"code\\gameflow\\start\\systeminit",0x4B8,0x75E,"System Initialization");
    produceAsmScript(file,"code\\common\\tech\\interrupts\\interrupts",0x75E,0x820,"Misc. Interruptions");
    produceAsmScript(file,"code\\common\\tech\\sound\\musicend",0x820,0x868,"Music end-related functions");
    produceAsmScript(file,"code\\common\\tech\\graphics\\vdp",0x868,0xFDA,"VDP functions");
    produceAsmSection(file,"",0xFDA,0x1040);
    produceAsmScript(file,"code\\common\\tech\\input",0x1040,0x1164,"Player input functions");
    produceAsmScript(file,"code\\common\\tech\\randomnumbergenerator",0x1164,0x1184,"Random Number Generator");
    produceAsmScript(file,"code\\common\\tech\\interrupts\\hint",0x1184,0x11DE,"Horizontal Interrupt");
    produceAsmScript(file,"code\\common\\tech\\interrupts\\vint",0x11DE,0x14F2,"Vertical Interrupt");
    produceAsmScript(file,"code\\common\\tech\\sram\\gamesaves",0x14F2,0x16B6,"Game save SRAM management");
    produceAsmScript(file,"code\\gameflow\\start\\gamestart",0x16B6,0x16DC,"Game start");
    produceAsmScript(file,"code\\gameflow\\mainloop",0x16DC,0x1788,"Main Loop");
    produceAsmSection(file,"",0x1788,0x2824);
    produceAsmScript(file,"code\\common\\maps\\mapengine",0x2824,0x2DCE,"Map Engine");
    produceAsmSection(file,"",0x2DCE,0xC59E);
    produceAsmScript(file,"data\\scripting\\text\\intro\\entries",0xC59E,0xC74E,"Intro Text Block Entries");
    produceAsmScript(file,"data\\maps\\global\\visitedmapsflags",0xC74E,0xCDAE,"Visited Maps Flag Map");
    produceAsmScript(file,"code\\common\\maps\\maploading",0xCDAE,0xD25C,"Map Loading");
    produceAsmSection(file,"",0xD25C,0x010300);

    fclose(file);
    Message("DONE.\n");    
}


static produceSectionSix(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\ls-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmSection(file,"",0x44010,0x44014);
    produceAsmScript(file,"data\\graphics\\maps\\tilesets\\animated\\entries",0x44014,0x4406C,"Animated Map Tileset Pointer Table");
    produceAsmSection(file,"",0x4406C,0x44070);
    produceAsmScript(file,"data\\graphics\\maps\\tilesets\\entries",0x44070,0x94F2A,"Map Tileset Entries");
    produceAsmScript(file,"data\\graphics\\maps\\tilesets\\animated\\storage",0x94F2A,0x9A4EA,"Map Tileset Entries");
    produceAsmSection(file,"",0x9A4EA,0x9B000);

    fclose(file);
    Message("DONE.\n");    
}





static produceSectionEight(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\ls-%s-0x0%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmSection(file,"",0xA0A00,0xA0A12);
    produceAsmScript(file,"data\\maps\\entries",0xA0A12,0x11C926,"Map entry list");
    produceAsmScript(file,"data\\graphics\\maps\\palettes\\entries",0x11C926,0x11CEA2,"Map palettes entry list");
    produceAsmScript(file,"data\\maps\\global\\mapwarps",0x11CEA2,0x11EA64,"Map warps");
    produceAsmScript(file,"code\\common\\tech\\regioncheck",0x11EA64,0x11F314,"Region check code");
    produceAsmSection(file,"",0x11F314,0x120000);

    fclose(file);
    Message("DONE.\n");    
}




static produceSectionNine(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\ls-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmSection(file,"",0x120000,0x120004);
    produceAsmScript(file,"data\\graphics\\sprites\\entries",0x120004,0x1A42DE,"Sprite entry tables");
    produceAsmSection(file,"",0x1A42DE,0x1A4400);

    fclose(file);
    Message("DONE.\n");    
}

static produceSectionTen(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\ls-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmSection(file,"",0x1A4400,0x1A453A);
    produceAsmScript(file,"data\\graphics\\sprites\\spritepalettes",0x1A453A,0x1A47E0,"Sprite Palette Map");
    produceAsmScript(file,"data\\graphics\\sprites\\palettes\\entries",0x1A47E0,0x1A4C8E,"Sprite Palette Entries");
    produceAsmSection(file,"",0x1A4C8E,0x1AF800);

    fclose(file);
    Message("DONE.\n");    
}


static produceSectionEleven(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\ls-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmSection(file,"",0x1AF800,0x1AF804);
    produceAsmScript(file,"data\\graphics\\maps\\blocks\\entries",0x1AF804,0x1DF9F8,"Map Block Entries");
    produceAsmSection(file,"",0x1DF9F8,0x1E0000);

    fclose(file);
    Message("DONE.\n");    
}





static produceAsmDataEntries(mainFile,sectionName,entryName,start,end,lastEntryDataEnd,chunkEnd,maxIndex,indexLength,sectionComment){
    auto fileName, file, addr, i, j, dref, dataEnd, from, index, entryFileName, entryComment;
    // Produce main file
    fileName = form("%sentries", sectionName);
    produceAsmScript(mainFile,fileName,start,end,sectionComment);
    file = fopen(form("disasm\\%s.asm", fileName),"a");
    // Produce individual entry files
    addr = start;
    i = 0;
    while(addr<end&&i<maxIndex){
        dref = Dfirst(addr);
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){dataEnd = j;}
                from = DnextB(addr,from);
            }
            j++;
            if(j==lastEntryDataEnd){dataEnd = lastEntryDataEnd;}
        }
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index = form("0%s", index);}
        entryFileName = form("%s%s%s", sectionName,entryName,index);
        entryComment = form("%s %s", sectionComment,index);
        produceAsmScript(file,entryFileName,dref,dataEnd,entryComment);
        addr = addr+4;
        i++;
    }
    if(lastEntryDataEnd<chunkEnd){produceAsmSection(file,"",lastEntryDataEnd,chunkEnd);}
    fclose(file);
}


static produceGenericSection(mainFile,sectionName,start,end,fs,sectionComment){
    produceSectionWithPrettyPrintParam(mainFile,sectionName,start,end,fs,sectionComment,1);
}


static produceSectionWithPrettyPrintParam(mainFile,sectionName,start,end,fs,sectionComment,prettyPrint){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    auto startString, endString;
    startString = ltoa(start,16);
    while(strlen(startString)<6){startString = form("0%s",startString);} 
    endString = ltoa(end,16);
    while(strlen(endString)<6){endString = form("0%s",endString);} 
    fileName = form("layout\\ls-%s-0x%s-0x%s.asm",sectionName,startString,endString);
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    //form("0x%s..0x%s %s",ltoa(start,16),ltoa(end,16),sectionComment)
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    
    ea = start;
    while(ea<end){
        itemSize = ItemSize(ea);
        if(GetFunctionAttr(ea,FUNCATTR_START)==ea){    
            writeFunctionHeader(file,ea,prettyPrint);
        }
        else if(GetFchunkAttr(ea,FUNCATTR_START)==ea){    
            writeFChunkHeader(file,ea,prettyPrint);
        }        
        writeItem(file,"",ea);
        if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFunctionFooter(file,ea,prettyPrint);
        }        
        else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFChunkFooter(file,ea,prettyPrint);
        }                
        ea = ea + itemSize;
    }
    fclose(file);
    Message("DONE.\n");    

}


static produceAsmScriptWithExtName(mainFile,extName,sectionName,start,end,sectionComment){
    produceAsmScriptWithConditionalInclude(mainFile,extName,sectionName,start,end,sectionComment,0);
}

static produceAsmScript(mainFile,sectionName,start,end,sectionComment){
    produceAsmScriptWithConditionalInclude(mainFile,"",sectionName,start,end,sectionComment,0);
}


static produceAsmScriptWithConditionalInclude(mainFile,extName,sectionName,start,end,sectionComment,conditionalIncludeType){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, include, name, indent, comment, commentEx, commentIndent, offsets;
    fileName = form("%s.asm",sectionName);
    Message(form("Writing assembly script section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    //form("0x%s..0x%s %s",ltoa(start,16),ltoa(end,16),sectionComment)
    action = 1;
    if(conditionalIncludeType==1){
        include = "includeIfVanillaRom";
    }else if(conditionalIncludeType==2){
        include = "includeIfExpandedRom";
    }else{
        include = "include";
    }
    indent = "                ";
    if(extName!=""){
        name = form("%s:",extName);
        while(strlen(name)<(strlen(indent))){
            name = form("%s ",name);
        }        
    }else{
        name = indent;
    }
    writestr(mainFile,form("%s%s \"%s\"    ; %s\n",name,include,fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    offsets = form("0x%s..0x%s",ltoa(start,16),ltoa(end,16));
    writestr(file,form("\n; ASM FILE %s.asm :\n; %s : %s\n",sectionName,offsets,sectionComment));
    produceAsmSection(file,extName,start,end);
    fclose(file);
    Message("DONE.\n");    

}

static produceAsmSection(file,extName,start,end){
    produceAsmSectionWithPrettyParam(file,extName,start,end,1);
}

static produceAsmSectionNoPretty(file,extName,start,end){
    produceAsmSectionWithPrettyParam(file,extName,start,end,0);
}

static produceAsmSectionWithPrettyParam(file,extName,start,end,prettyWriteFunctions){
    auto ea,itemSize;
    ea = start;
    while(ea<end){
        itemSize = ItemSize(ea);
        if(GetFunctionAttr(ea,FUNCATTR_START)==ea){    
            writeFunctionHeader(file,ea,prettyWriteFunctions);
        }
        else if(GetFchunkAttr(ea,FUNCATTR_START)==ea){    
            writeFChunkHeader(file,ea,prettyWriteFunctions);
        }        
        writeItemWithPrettyPrintParam(file,extName,ea,prettyWriteFunctions);
        if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFunctionFooter(file,ea,prettyWriteFunctions);
        }        
        else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFChunkFooter(file,ea,prettyWriteFunctions);
        }                
        ea = ea + itemSize;
    }
}

static writeHeader(file){
    writestr(file,"\n");
    writestr(file,"   include \"lsmacros.asm\"\n");
    writestr(file,"   include \"lspatches.asm\"\n");    
    writestr(file,"   include \"lsenums.asm\"\n");
    writestr(file,"   include \"lsconst.asm\"\n");
    writestr(file,"\n");
    writestr(file,"   include \"layout\\ls-00-romlayout.asm\"\n");
}

static writeFooter(file){
    writestr(file,"        END");
}

static writeFunctionHeader(file, ea, prettyWriteFunctions){
    auto funcCmt;
    if(prettyWriteFunctions!=0){
        writestr(file,"\n; =============== S U B R O U T I N E =======================================\n\n");
    }
    funcCmt = GetFunctionCmt(ea,0);
    if(funcCmt!=""){
        writestr(file,form("; %s\n",funcCmt));
        if(prettyWriteFunctions!=0){
            writestr(file,"\n");
        }
    }
    else{
        funcCmt = GetFunctionCmt(ea,1);
        if(funcCmt!=""){
            funcCmt = formatFuncRptCmt(funcCmt);
            writestr(file,form("; %s\n",funcCmt));
            if(prettyWriteFunctions!=0){
                writestr(file,"\n");
            }            
        }
    }
    undefineLocalVars(file,ea);
}

static undefineLocalVars(file,ea){
    auto id, i, firstM, lastM, mName, mSize, mFlag;
    id = GetFrame(ea);
    firstM = GetFirstMember(id);
    lastM = GetLastMember(id);
    i=firstM;
    while(i<=lastM){
        if(i!=-1&&GetMemberName(id,i)!=""&&GetMemberName(id,i)!=" r"&&GetMemberName(id,i)!=" s"){
            mName = GetMemberName(id,i); // Get the name
            mSize = GetMemberSize(id, i); // Get the size (in byte)
            mFlag = GetMemberFlag(id, i); // Get the flag
            Message("\n%a : undefined %s %d %x", ea, mName, mSize, mFlag);
            DelStrucMember(id,i);        
            i = i+mSize;
        }
        else{
            i++;
        }    
    }
}

static undefineMultipleLineArray(ea){
    auto type;
            type = GuessType(ea);
            if(strstr(type,"char[")!=-1&&(strstr(GetDisasm(ea),"incbin")==-1)){
                    Message(form("\n%a : %s     <== UNDEFINE if on multiple lines.",ea,GuessType(ea)));
            }    
}

static writeFunctionFooter(file, ea,prettyWriteFunctions){
    auto funcName;
    funcName = GetFunctionName(ea);
    if(prettyWriteFunctions!=0){
        writestr(file,form("\n    ; End of function %s\n\n",funcName));
    }
}

static writeItem(file,extName,ea){
    writeItemWithPrettyPrintParam(file,extName,ea,1);
}

static writeItemWithPrettyPrintParam(file,extName,ea,prettyPrint){
    auto name,ln,indent,disasm,cmtIdx,commentIndent,comment,commentEx,lineA,lineB,disasmLen,manualInsn,output;
    auto i,next;
    indent = "                ";
    commentIndent = "                                        ";
    //name = GetTrueName(ea);
    name = GetTrueNameEx(ea,ea);        // Get local label name if it exists
    if(name==""){
        name = Name(ea);
    }
    if(name!=""&&name!=extName){
        name=form("%s:",name);
        if(GetFunctionAttr(ea,FUNCATTR_START)!=-1){
            if(prettyPrint!=0){
                ln = "\n";
            }else{
                ln = "";
            }
            name = form("%s%s%s",name,ln,indent);
        }
        else{
            while(strlen(name)<(strlen(indent))){
                name = form("%s ",name);
            }        
            undefineMultipleLineArray(ea);
        }
    }
    else {
        name = indent;
    }
    commentEx = CommentEx(ea,0);
    if(commentEx!=""){
        comment = commentEx;
    }
    else{
        commentEx = CommentEx(ea,1);
        if(commentEx!=""){
            comment = formatRptCmt(commentEx);
        }
    }
    //lineA = LineA(ea,0);
    disasm = GetDisasm(ea);
    cmtIdx = strstr(disasm,";");
    //lineB = LineB(ea,0);
    if(cmtIdx!=-1){
        disasm = substr(disasm,0,cmtIdx);
    }
    if(comment!="" && comment!=" "){
        comment = form("; %s",comment);
    }
    if(strlen(name)>(strlen(indent))){
        name = form("%s\n%s",name,indent);
    }
    if(strstr(lineA,"\n")!=-1){
        lineA = form("%s%s",lineA,indent);
    }
    
    // Make sure there is at least one space between disasm and comment
    disasmLen = strlen(indent)+strlen(disasm);
    if(disasmLen==strlen(commentIndent)&&substr(disasm,strlen(disasm)-1,-1)!=" "){disasmLen = disasmLen+1;}
    if(disasmLen>strlen(commentIndent)&&comment!=""&&comment!=" "){
        disasm = form("%s%s", disasm," ");
    }
    // Put comment on a new line if disasm reached a certain length
    if(strlen(disasm)>strlen(commentIndent)+12&&comment!=""&&comment!=" "){
        disasm = form("%s\n%s%s",disasm,indent,commentIndent);
    }
    // Handle manual instructions spanning multiple lines
    manualInsn = substr(GetManualInsn(ea),strstr(GetManualInsn(ea),"\n"),-1);
    if(manualInsn!=""){manualInsn = formatManualInsn(substr(manualInsn,1,-1));}
    //Message(form("\nname=%s,lineA=%s,disasm=%s,comment=%s,lineB=%s",name,lineA,disasm,comment,lineB));
    
    //output = form("%s%s%s%s\n%s%s",name,lineA,disasm,comment,lineB,manualInsn);
    //writestr(file,output);
    
    writestr(file,name);
    /* Support producing multiple additional lines */
    i = 0;
    lineA = "";
    while(LineA(ea,i)!="" && LineA(ea,i)!=" "){
        lineA = form("%s\n",LineA(ea,i));
        if(i==0 && strstr(lineA,indent)!=-1){
            lineA = substr(lineA,strlen(indent),-1);
        }
        writestr(file,lineA);
        i++;
        if(LineA(ea,i)=="" || LineA(ea,i)==" "){
            writestr(file,indent);
            break;
        }
    }
    writestr(file,form("%s%s\n",disasm,comment));
    /* Same as above */
    i = 0;
    lineB = "";
    while(LineB(ea,i)!="" && LineB(ea,i)!=" "){
        lineB = form("%s\n",LineB(ea,i));
        writestr(file,lineB);
        i++;
    }
    writestr(file,manualInsn);
}

static writeFChunkHeader(file,ea,prettyWriteFunctions){
    auto text,functionName;
    text = "; START OF FUNCTION CHUNK FOR ";
    functionName = GetFunctionName(ea);
    writestr(file,form("\n%s%s\n\n",text,functionName));
}

static writeFChunkFooter(file,ea,prettyWriteFunctions){
    auto text,functionName;
    text = "; END OF FUNCTION CHUNK FOR ";
    functionName = GetFunctionName(ea);
    writestr(file,form("\n%s%s\n\n",text,functionName));
}

static formatFuncRptCmt(cmt){
    auto index, before, after, result;
    index = strstr(cmt,"\n");
    if(index!=-1){
        before = substr(cmt,0,index+1);
        after = substr(cmt,index+1,strlen(cmt));
        result = form("%s; %s",before,formatFuncRptCmt(after));
        return result;
    }
    else{
        return cmt;
    }
}

static formatRptCmt(cmt){
    auto index, before, after, result;
    index = strstr(cmt,"\n");
    if(index!=-1){
        before = substr(cmt,0,index+1);
        after = substr(cmt,index+1,strlen(cmt));
        result = form("%s                                        ; %s",before,formatRptCmt(after));
        return result;
    }
    else{
        return cmt;
    }
}

static formatManualInsn(manualInsn){
    auto result, indent, searcher, next;
    result = "";
    indent = "                    ";
    searcher = indent+manualInsn;
    next = 0;
    while(next!=-1){
        next = strstr(searcher,"\n");
        if(next==-1)
            break;
        result = result+substr(searcher,0,next)+"\n"+indent;
        searcher = substr(searcher,next+1,-1);
    }
    result = result+searcher+"\n";
    return result;
}




    /* useless
    i=0;
    line = LineA(ea,i);
    while(line!=""){
        lineA = form("%s\n%s",lineA,line);
        i++;
        line = LineA(ea,i);
    }
    if(lineA!=""){
        lineA = form("%s\n",lineA);
    }
    
    i=0;
    line = LineB(ea,i);
    while(line!=""){
        lineA = form("%s\n%s",lineB,line);
        i++;
        line = LineB(ea,i);        
    }
    if(lineB!=""){
        lineB = form("%s\n",lineB);
    }
    */