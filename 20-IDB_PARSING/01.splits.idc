

#include <idc.idc>



static main(void){


    splitAll();


}







static splitAll(){
    auto file;

    Message("SPLITTING...\n");
    file = fopen("lssplits.txt","w");
    initFile(file);

    Message("Pointer Tables...");
    splitPTs(file);
    Message(" DONE.\nSingle Chunks...");    
    splitSingleChunks(file); 
    Message(" DONE.\nSprites ...");
    splitSprites(file);
    Message(" DONE.\nMaps ...");
    splitMaps(file);
    Message(" DONE.\nMap Tilesets ...");
    splitMapTilesets(file);
    Message(" DONE.\nAnimated Map Tilesets ...");
    splitAnimatedMapTilesets(file);
    Message(" DONE.\nMap Blocks ...");
    splitMapBlocks(file);
    /* SF2-specific examples   
    Message(" DONE.\nMapsprites ...");
    splitMapsprites(file);
    Message(" DONE.\nMaps ...");
    splitMaps(file);
    Message(" DONE.\nGrounds...");    
    splitGrounds(file);
    Message(" DONE.\nTextBanks...");    
    splitTextbanks(file);
    */
    Message(" DONE.\n");    
    
    writestr(file,"\nsplit    0x0,0x0,\\0x0 - .bin\n");
    fclose(file);
    Message("END OF SPLITS.\n");    
    
}


static initFile(file){
writestr(file,"/***********************Directories***************************/\n");
writestr(file,"#dir    data/\n");
/* SF2 examples
writestr(file,"#dir    data/graphics/\n");
writestr(file,"#dir    data/graphics/portraits\n");
writestr(file,"#dir    data/graphics/mapsprites\n");
writestr(file,"#dir    data/graphics/specialsprites\n");
writestr(file,"#dir    data/graphics/battles\n");
writestr(file,"#dir    data/graphics/battles/battlesprites\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/allies\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/allies/animations/\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/enemies\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/enemies/animations/\n");
writestr(file,"#dir    data/graphics/battles/weapons\n");
writestr(file,"#dir    data/graphics/battles/spells\n");
writestr(file,"#dir    data/graphics/battles/spells/invocations/\n");
writestr(file,"#dir    data/graphics/battles/spells/animations/\n");
writestr(file,"#dir    data/graphics/battles/backgrounds\n");
writestr(file,"#dir    data/graphics/battles/grounds\n");
writestr(file,"#dir    data/graphics/specialscreens\n");
writestr(file,"#dir    data/graphics/specialscreens/titlescreen\n");
writestr(file,"#dir    data/graphics/specialscreens/witchscreen\n");
writestr(file,"#dir    data/graphics/specialscreens/suspendscreen\n");
writestr(file,"#dir    data/graphics/specialscreens/endingkiss\n");
writestr(file,"#dir    data/graphics/specialscreens/endingjewels\n");
writestr(file,"#dir    data/graphics/maps\n");
writestr(file,"#dir    data/graphics/maps/tilesets\n");
writestr(file,"#dir    data/graphics/maps/palettes\n");
writestr(file,"#dir    data/graphics/icons\n");
writestr(file,"#dir    data/graphics/tech\n");
writestr(file,"#dir    data/graphics/tech/menus\n");
writestr(file,"#dir    data/graphics/tech/fonts\n");
writestr(file,"#dir    data/graphics/tech/windowlayouts\n");
writestr(file,"#dir    data/maps/\n");
writestr(file,"#dir    data/maps/global/\n");
writestr(file,"#dir    data/maps/entries/\n");
writeMapEntries(file);
writestr(file,"#dir    data/battles/\n");
writestr(file,"#dir    data/battles/global/\n");
writestr(file,"#dir    data/battles/entries/\n");
writeBattleEntries(file);
writestr(file,"#dir    data/stats\n");
writestr(file,"#dir    data/stats/items\n");
writestr(file,"#dir    data/stats/spells\n");
writestr(file,"#dir    data/stats/allies/\n");
writestr(file,"#dir    data/stats/allies/classes\n");
writestr(file,"#dir    data/stats/allies/stats\n");
writestr(file,"#dir    data/stats/enemies/\n");
writestr(file,"#dir    data/tech/\n");
writestr(file,"#dir    data/scripting/\n");
writestr(file,"#dir    data/scripting/text\n");
*/
writestr(file,"#dir    data/sound\n");
writestr(file,"#dir    data/scripting\n");
writestr(file,"#dir    data/scripting/text\n");
writestr(file,"#dir    data/scripting/text/intro\n");
writestr(file,"#dir    data/graphics\n");
writestr(file,"#dir    data/graphics/specialscreens\n");
writestr(file,"#dir    data/graphics/sprites\n");
writestr(file,"#dir    data/graphics/sprites/palettes\n");
writestr(file,"#dir    data/graphics/maps\n");
writestr(file,"#dir    data/graphics/maps/palettes\n");
writestr(file,"#dir    data/graphics/maps/tilesets\n");
writestr(file,"#dir    data/graphics/maps/tilesets/animated\n");
writestr(file,"#dir    data/graphics/maps/blocks\n");
writestr(file,"#dir    data/graphics/tech\n");
writestr(file,"#dir    data/graphics/tech/fonts\n");
writestr(file,"#dir    data/graphics/tech/menus\n");
writestr(file,"#dir    data/maps/\n");
writestr(file,"#dir    data/maps/global/\n");
writestr(file,"#dir    data/maps/entries/\n");
writeMapEntries(file);
writestr(file,"\n");
writestr(file,"/***********************Data***************************/\n");
writestr(file,"\n");
}

/*

static writeBattleEntries(file){
    auto i,index;
    for(i=0;i<=44;i++){
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        writestr(file,form("#dir\tdata/battles/entries/battle%s\n",index));
    }
}

*/

static writeMapEntries(file){
    auto i,index;
    for(i=0;i<=815;i++){
        index = ltoa(i,10);
        while(strlen(index)<3){index=form("0%s",index);}
        writestr(file,form("#dir\tdata/maps/entries/map%s\n",index));
    }
}


/*
 *  Split simple pointer tables
 */
static splitPTs(file){

    /*  Template
     *  splitPT(start, end, lastEntryDataEnd, chunkEnd, "ptName", "entryName", "binDir", 0, "binName", indexLength, align, file);
     */
     /* SF2 examples
    splitPT(0x6400C, 0x641D8, 0x9494A, 0x9494A, "pt_MapTilesets", "MapTileset", "data/graphics/maps/maptilesets/", 0, "maptileset", 3, 0, file);
    splitPT(0x9494A, 0x9498A, 0x94B8A, 0x94B8A, "pt_MapPalettes", "MapPalette", "data/graphics/maps/mappalettes/", 0, "mappalette", 2, 0, file);        
    //splitPT(0xC8000, 0xC8B40, 0xFFC48, 0x100000, "pt_MapSprites", "MapSprite", "data/graphics/mapsprites/", 0, "mapsprite", 3, 15, file);    
    splitPT(0x101EE0, 0x101F58, 0x12A2F8, 0x12A2F8, "pt_Backgrounds", "Background", "data/graphics/battles/backgrounds/", 0, "background", 2, 0, file);
    splitPT(0x130004, 0x1300DC, 0x17FE4F, 0x180000, "pt_EnemyBattleSprites", "EnemyBattleSprite", "data/graphics/battles/battlesprites/enemies/", 0, "enemybattlesprite", 2, 15, file);
    splitPT(0x18001C, 0x18009C, 0x1AA16E, 0x1AA16E, "pt_AllyBattleSprites", "AllyBattleSprite", "data/graphics/battles/battlesprites/allies/", 0, "allybattlesprite", 2, 0, file);
    splitPT(0x1AAC3A, 0x1AAD96, 0x1AB79E, 0x1AB79E, "pt_AlliesAnimations", "AllyAnimation", "data/graphics/battles/battlesprites/allies/animations/", 0, "allybattlespriteanimation", 3, 0, file);
    splitPT(0x1AB79E, 0x1AB982, 0x1ABE52, 0x1AC000, "pt_EnemyAnimations", "EnemyAnimation", "data/graphics/battles/battlesprites/enemies/animations/", 0, "enemybattlespriteanimation", 3, 14, file);
    splitPT(0x1AD104, 0x1AD1B8, 0x1B120A, 0x1B120A, "pt_BattleTerrainData", "BattleTerrain", "data/battles/entries/battle", 1, "/terrain", 2, 0, file);
    splitPT(0x1B30EE, 0x1B31A2, 0x1B6DB0, 0x1B6DB0, "pt_BattleSpriteSets", "BattleSpriteSet", "data/battles/entries/battle", 1, "/spriteset", 2, 0, file);
    splitPT(0x1B9A9A, 0x1B9AF6, 0x1BEE38, 0x1BEE38, "pt_WeaponSprites", "WeaponSprite", "data/graphics/battles/weapons/", 0, "weaponsprite", 2, 0, file);                    
    splitPT(0x1BEEE0, 0x1BEF3C, 0x1C46C2, 0x1C46C2, "pt_SpellGraphics", "SpellGraphics", "data/graphics/battles/spells/", 0, "spellgraphics", 2, 0, file);
    splitPT(0x1C8004, 0x1C80E4, 0x1D7E26, 0x1D8000, "pt_Portraits", "Portrait", "data/graphics/portraits/", 0, "portrait", 2, 15, file);
    //splitPT(0x1EE270, 0x1EE2F0, 0x1EE7D0, 0x1EE7D0, "pt_AllyStats", "AllyStats", "data/stats/allies/stats/", 0, "allystats", 2, 0, file);
    */

}

static splitSingleChunks(file) {
    auto i,j,x,s,index,path;
    auto start,base,addr,end,dref,section,action;
    
    // Template : splitSingleChunk(0x,0x,"","",file);
    
    
    splitSingleChunk(0x009242, 0x0095AC, "StatusBarTileset","data/graphics/tech/menus/statusbartileset.bin",file);
    
    splitSingleChunk(0x00C5CE, 0x00C5F4, "IntroTextBlock00","data/scripting/text/intro/introtextblock00.bin",file);
    splitSingleChunk(0x00C5F4, 0x00C618, "IntroTextBlock01","data/scripting/text/intro/introtextblock01.bin",file);
    splitSingleChunk(0x00C618, 0x00C640, "IntroTextBlock02","data/scripting/text/intro/introtextblock02.bin",file);
    splitSingleChunk(0x00C640, 0x00C662, "IntroTextBlock03","data/scripting/text/intro/introtextblock03.bin",file);
    splitSingleChunk(0x00C662, 0x00C67E, "IntroTextBlock04","data/scripting/text/intro/introtextblock04.bin",file);
    splitSingleChunk(0x00C67E, 0x00C6A4, "IntroTextBlock05","data/scripting/text/intro/introtextblock05.bin",file);
    splitSingleChunk(0x00C6A4, 0x00C6C0, "IntroTextBlock06","data/scripting/text/intro/introtextblock06.bin",file);
    splitSingleChunk(0x00C6C0, 0x00C6DC, "IntroTextBlock07","data/scripting/text/intro/introtextblock07.bin",file);
    splitSingleChunk(0x00C6DC, 0x00C6F8, "IntroTextBlock08","data/scripting/text/intro/introtextblock08.bin",file);
    splitSingleChunk(0x00C6F8, 0x00C714, "IntroTextBlock09","data/scripting/text/intro/introtextblock09.bin",file);
    splitSingleChunk(0x00C714, 0x00C732, "IntroTextBlock10","data/scripting/text/intro/introtextblock10.bin",file);
    splitSingleChunk(0x00C732, 0x00C74E, "IntroTextBlock11","data/scripting/text/intro/introtextblock11.bin",file);
    
    splitSingleChunk(0x00FD5C, 0x00FE37, "SaveScreenTileset1","data/graphics/specialscreens/savescreentileset1.bin",file);
    splitSingleChunk(0x00FE37, 0x00FF12, "SaveScreenTileset2","data/graphics/specialscreens/savescreentileset2.bin",file);
    
    splitSingleChunk(0x02A884, 0x02B27A, "MainFont","data/graphics/tech/fonts/mainfont.bin",file);
    splitSingleChunk(0x02B27A, 0x02C29B, "TextBank0","data/scripting/text/textbank0.bin",file);
    splitSingleChunk(0x02C29B, 0x02DCC8, "TextBank1","data/scripting/text/textbank1.bin",file);
    splitSingleChunk(0x02DCC8, 0x02F787, "TextBank2","data/scripting/text/textbank2.bin",file);
    splitSingleChunk(0x02F787, 0x03153E, "TextBank3","data/scripting/text/textbank3.bin",file);
    splitSingleChunk(0x03153E, 0x0330AB, "TextBank4","data/scripting/text/textbank4.bin",file);
    splitSingleChunk(0x0330AB, 0x034830, "TextBank5","data/scripting/text/textbank5.bin",file);
    splitSingleChunk(0x034830, 0x036087, "TextBank6","data/scripting/text/textbank6.bin",file);
    splitSingleChunk(0x036087, 0x0377E3, "TextBank7","data/scripting/text/textbank7.bin",file);
    splitSingleChunk(0x0377E3, 0x038368, "TextBank8","data/scripting/text/textbank8.bin",file);
    
    splitSingleChunk(0x0386E4, 0x0389D4, "SegaLogoTileset","data/graphics/specialscreens/segalogotileset.bin",file);
    
    splitSingleChunk(0x039ED8, 0x03A564, "TitleScreenTileset1","data/graphics/specialscreens/titlescreentileset1.bin",file);
    splitSingleChunk(0x03A564, 0x03BCAE, "TitleScreenTileset2","data/graphics/specialscreens/titlescreentileset2.bin",file);
    splitSingleChunk(0x03BCAE, 0x03DD92, "TitleScreenTileset3","data/graphics/specialscreens/titlescreentileset3.bin",file);
    splitSingleChunk(0x03DD92, 0x03DDFE, "TitleScreenLayout1","data/graphics/specialscreens/titlescreenlayout1.bin",file);
    splitSingleChunk(0x03DDFE, 0x03DE52, "TitleScreenLayout2","data/graphics/specialscreens/titlescreenlayout2.bin",file);
    splitSingleChunk(0x03DE52, 0x03DECA, "TitleScreenLayout3","data/graphics/specialscreens/titlescreenlayout3.bin",file);
    splitSingleChunk(0x03DECA, 0x03DEEA, "TitleScreenPalette1","data/graphics/specialscreens/titlescreenpalette1.bin",file);
    splitSingleChunk(0x03DEEA, 0x03DF0A, "TitleScreenPalette2","data/graphics/specialscreens/titlescreenpalette2.bin",file);
    splitSingleChunk(0x03DF8A, 0x03E621, "ClimaxLogoTileset","data/graphics/specialscreens/climaxlogotileset.bin",file);
    splitSingleChunk(0x03E621, 0x03E64C, "ClimaxLogoLayout","data/graphics/specialscreens/climaxlogolayout.bin",file);
    splitSingleChunk(0x03E64C, 0x03E654, "ClimaxLogoPalette","data/graphics/specialscreens/climaxlogopalette.bin",file);
    
    splitSingleChunk(0x09A4EA, 0x09AC6C, "IntroFont","data/graphics/tech/fonts/introfont.bin",file);
    
    splitSingleChunk(0x11C926+0*26,   0x11C926+0*26+26,   "MapPalette00","data/graphics/maps/palettes/mappalette00.bin",file);
    splitSingleChunk(0x11C926+1*26,   0x11C926+1*26+26,   "MapPalette01","data/graphics/maps/palettes/mappalette01.bin",file);
    splitSingleChunk(0x11C926+2*26,   0x11C926+2*26+26,   "MapPalette02","data/graphics/maps/palettes/mappalette02.bin",file);
    splitSingleChunk(0x11C926+3*26,   0x11C926+3*26+26,   "MapPalette03","data/graphics/maps/palettes/mappalette03.bin",file);
    splitSingleChunk(0x11C926+4*26,   0x11C926+4*26+26,   "MapPalette04","data/graphics/maps/palettes/mappalette04.bin",file);
    splitSingleChunk(0x11C926+5*26,   0x11C926+5*26+26,   "MapPalette05","data/graphics/maps/palettes/mappalette05.bin",file);
    splitSingleChunk(0x11C926+6*26,   0x11C926+6*26+26,   "MapPalette06","data/graphics/maps/palettes/mappalette06.bin",file);
    splitSingleChunk(0x11C926+7*26,   0x11C926+7*26+26,   "MapPalette07","data/graphics/maps/palettes/mappalette07.bin",file);
    splitSingleChunk(0x11C926+8*26,   0x11C926+8*26+26,   "MapPalette08","data/graphics/maps/palettes/mappalette08.bin",file);
    splitSingleChunk(0x11C926+9*26,   0x11C926+9*26+26,   "MapPalette09","data/graphics/maps/palettes/mappalette09.bin",file);
    splitSingleChunk(0x11C926+10*26,  0x11C926+10*26+26,  "MapPalette10","data/graphics/maps/palettes/mappalette10.bin",file);
    splitSingleChunk(0x11C926+11*26,  0x11C926+11*26+26,  "MapPalette11","data/graphics/maps/palettes/mappalette11.bin",file);
    splitSingleChunk(0x11C926+12*26,  0x11C926+12*26+26,  "MapPalette12","data/graphics/maps/palettes/mappalette12.bin",file);
    splitSingleChunk(0x11C926+13*26,  0x11C926+13*26+26,  "MapPalette13","data/graphics/maps/palettes/mappalette13.bin",file);
    splitSingleChunk(0x11C926+14*26,  0x11C926+14*26+26,  "MapPalette14","data/graphics/maps/palettes/mappalette14.bin",file);
    splitSingleChunk(0x11C926+15*26,  0x11C926+15*26+26,  "MapPalette15","data/graphics/maps/palettes/mappalette15.bin",file);
    splitSingleChunk(0x11C926+16*26,  0x11C926+16*26+26,  "MapPalette16","data/graphics/maps/palettes/mappalette16.bin",file);
    splitSingleChunk(0x11C926+17*26,  0x11C926+17*26+26,  "MapPalette17","data/graphics/maps/palettes/mappalette17.bin",file);
    splitSingleChunk(0x11C926+18*26,  0x11C926+18*26+26,  "MapPalette18","data/graphics/maps/palettes/mappalette18.bin",file);
    splitSingleChunk(0x11C926+19*26,  0x11C926+19*26+26,  "MapPalette19","data/graphics/maps/palettes/mappalette19.bin",file);
    splitSingleChunk(0x11C926+20*26,  0x11C926+20*26+26,  "MapPalette20","data/graphics/maps/palettes/mappalette20.bin",file);
    splitSingleChunk(0x11C926+21*26,  0x11C926+21*26+26,  "MapPalette21","data/graphics/maps/palettes/mappalette21.bin",file);
    splitSingleChunk(0x11C926+22*26,  0x11C926+22*26+26,  "MapPalette22","data/graphics/maps/palettes/mappalette22.bin",file);
    splitSingleChunk(0x11C926+23*26,  0x11C926+23*26+26,  "MapPalette23","data/graphics/maps/palettes/mappalette23.bin",file);
    splitSingleChunk(0x11C926+24*26,  0x11C926+24*26+26,  "MapPalette24","data/graphics/maps/palettes/mappalette24.bin",file);
    splitSingleChunk(0x11C926+25*26,  0x11C926+25*26+26,  "MapPalette25","data/graphics/maps/palettes/mappalette25.bin",file);
    splitSingleChunk(0x11C926+26*26,  0x11C926+26*26+26,  "MapPalette26","data/graphics/maps/palettes/mappalette26.bin",file);
    splitSingleChunk(0x11C926+27*26,  0x11C926+27*26+26,  "MapPalette27","data/graphics/maps/palettes/mappalette27.bin",file);
    splitSingleChunk(0x11C926+28*26,  0x11C926+28*26+26,  "MapPalette28","data/graphics/maps/palettes/mappalette28.bin",file);
    splitSingleChunk(0x11C926+29*26,  0x11C926+29*26+26,  "MapPalette29","data/graphics/maps/palettes/mappalette29.bin",file);
    splitSingleChunk(0x11C926+30*26,  0x11C926+30*26+26,  "MapPalette30","data/graphics/maps/palettes/mappalette30.bin",file);
    splitSingleChunk(0x11C926+31*26,  0x11C926+31*26+26,  "MapPalette31","data/graphics/maps/palettes/mappalette31.bin",file);
    splitSingleChunk(0x11C926+32*26,  0x11C926+32*26+26,  "MapPalette32","data/graphics/maps/palettes/mappalette32.bin",file);
    splitSingleChunk(0x11C926+33*26,  0x11C926+33*26+26,  "MapPalette33","data/graphics/maps/palettes/mappalette33.bin",file);
    splitSingleChunk(0x11C926+34*26,  0x11C926+34*26+26,  "MapPalette34","data/graphics/maps/palettes/mappalette34.bin",file);
    splitSingleChunk(0x11C926+35*26,  0x11C926+35*26+26,  "MapPalette35","data/graphics/maps/palettes/mappalette35.bin",file);
    splitSingleChunk(0x11C926+36*26,  0x11C926+36*26+26,  "MapPalette36","data/graphics/maps/palettes/mappalette36.bin",file);
    splitSingleChunk(0x11C926+37*26,  0x11C926+37*26+26,  "MapPalette37","data/graphics/maps/palettes/mappalette37.bin",file);
    splitSingleChunk(0x11C926+38*26,  0x11C926+38*26+26,  "MapPalette38","data/graphics/maps/palettes/mappalette38.bin",file);
    splitSingleChunk(0x11C926+39*26,  0x11C926+39*26+26,  "MapPalette39","data/graphics/maps/palettes/mappalette39.bin",file);
    splitSingleChunk(0x11C926+40*26,  0x11C926+40*26+26,  "MapPalette40","data/graphics/maps/palettes/mappalette40.bin",file);
    splitSingleChunk(0x11C926+41*26,  0x11C926+41*26+26,  "MapPalette41","data/graphics/maps/palettes/mappalette41.bin",file);
    splitSingleChunk(0x11C926+42*26,  0x11C926+42*26+26,  "MapPalette42","data/graphics/maps/palettes/mappalette42.bin",file);
    splitSingleChunk(0x11C926+43*26,  0x11C926+43*26+26,  "MapPalette43","data/graphics/maps/palettes/mappalette43.bin",file);
    splitSingleChunk(0x11C926+44*26,  0x11C926+44*26+26,  "MapPalette44","data/graphics/maps/palettes/mappalette44.bin",file);
    splitSingleChunk(0x11C926+45*26,  0x11C926+45*26+26,  "MapPalette45","data/graphics/maps/palettes/mappalette45.bin",file);
    splitSingleChunk(0x11C926+46*26,  0x11C926+46*26+26,  "MapPalette46","data/graphics/maps/palettes/mappalette46.bin",file);
    splitSingleChunk(0x11C926+47*26,  0x11C926+47*26+26,  "MapPalette47","data/graphics/maps/palettes/mappalette47.bin",file);
    splitSingleChunk(0x11C926+48*26,  0x11C926+48*26+26,  "MapPalette48","data/graphics/maps/palettes/mappalette48.bin",file);
    splitSingleChunk(0x11C926+49*26,  0x11C926+49*26+26,  "MapPalette49","data/graphics/maps/palettes/mappalette49.bin",file);
    splitSingleChunk(0x11C926+50*26,  0x11C926+50*26+26,  "MapPalette50","data/graphics/maps/palettes/mappalette50.bin",file);
    splitSingleChunk(0x11C926+51*26,  0x11C926+51*26+26,  "MapPalette51","data/graphics/maps/palettes/mappalette51.bin",file);
    splitSingleChunk(0x11C926+52*26,  0x11C926+52*26+26,  "MapPalette52","data/graphics/maps/palettes/mappalette52.bin",file);
    splitSingleChunk(0x11C926+53*26,  0x11C926+53*26+26,  "MapPalette53","data/graphics/maps/palettes/mappalette53.bin",file);    
    
    splitSingleChunk(0x11EBB4, 0x11F314, "RegionLockFont","data/graphics/tech/fonts/regionlockfont.bin",file);
    
    for(j=0x1A47E1;j<0x1A4BA0+16*14+8;j++){undefineByte(j);}
    
    splitSingleChunk(0x1A47E0+12*0,   0x1A47E0+12*0+12,   "SpritePalette000","data/graphics/sprites/palettes/spritepalette000.bin",file);
    splitSingleChunk(0x1A47E0+12*1,   0x1A47E0+12*1+12,   "SpritePalette001","data/graphics/sprites/palettes/spritepalette001.bin",file);
    splitSingleChunk(0x1A47E0+12*2,   0x1A47E0+12*2+12,   "SpritePalette002","data/graphics/sprites/palettes/spritepalette002.bin",file);
    splitSingleChunk(0x1A47E0+12*3,   0x1A47E0+12*3+12,   "SpritePalette003","data/graphics/sprites/palettes/spritepalette003.bin",file);
    splitSingleChunk(0x1A47E0+12*4,   0x1A47E0+12*4+12,   "SpritePalette004","data/graphics/sprites/palettes/spritepalette004.bin",file);
    splitSingleChunk(0x1A47E0+12*5,   0x1A47E0+12*5+12,   "SpritePalette005","data/graphics/sprites/palettes/spritepalette005.bin",file);
    splitSingleChunk(0x1A47E0+12*6,   0x1A47E0+12*6+12,   "SpritePalette006","data/graphics/sprites/palettes/spritepalette006.bin",file);
    splitSingleChunk(0x1A47E0+12*7,   0x1A47E0+12*7+12,   "SpritePalette007","data/graphics/sprites/palettes/spritepalette007.bin",file);
    splitSingleChunk(0x1A47E0+12*8,   0x1A47E0+12*8+12,   "SpritePalette008","data/graphics/sprites/palettes/spritepalette008.bin",file);
    splitSingleChunk(0x1A47E0+12*9,   0x1A47E0+12*9+12,   "SpritePalette009","data/graphics/sprites/palettes/spritepalette009.bin",file);
    splitSingleChunk(0x1A47E0+12*10,  0x1A47E0+12*10+12,  "SpritePalette010","data/graphics/sprites/palettes/spritepalette010.bin",file);
    splitSingleChunk(0x1A47E0+12*11,  0x1A47E0+12*11+12,  "SpritePalette011","data/graphics/sprites/palettes/spritepalette011.bin",file);
    splitSingleChunk(0x1A47E0+12*12,  0x1A47E0+12*12+12,  "SpritePalette012","data/graphics/sprites/palettes/spritepalette012.bin",file);
    splitSingleChunk(0x1A47E0+12*13,  0x1A47E0+12*13+12,  "SpritePalette013","data/graphics/sprites/palettes/spritepalette013.bin",file);
    splitSingleChunk(0x1A47E0+12*14,  0x1A47E0+12*14+12,  "SpritePalette014","data/graphics/sprites/palettes/spritepalette014.bin",file);
    splitSingleChunk(0x1A47E0+12*15,  0x1A47E0+12*15+12,  "SpritePalette015","data/graphics/sprites/palettes/spritepalette015.bin",file);
    splitSingleChunk(0x1A47E0+12*16,  0x1A47E0+12*16+12,  "SpritePalette016","data/graphics/sprites/palettes/spritepalette016.bin",file);
    splitSingleChunk(0x1A47E0+12*17,  0x1A47E0+12*17+12,  "SpritePalette017","data/graphics/sprites/palettes/spritepalette017.bin",file);
    splitSingleChunk(0x1A47E0+12*18,  0x1A47E0+12*18+12,  "SpritePalette018","data/graphics/sprites/palettes/spritepalette018.bin",file);
    splitSingleChunk(0x1A47E0+12*19,  0x1A47E0+12*19+12,  "SpritePalette019","data/graphics/sprites/palettes/spritepalette019.bin",file);
    splitSingleChunk(0x1A47E0+12*20,  0x1A47E0+12*20+12,  "SpritePalette020","data/graphics/sprites/palettes/spritepalette020.bin",file);
    splitSingleChunk(0x1A47E0+12*21,  0x1A47E0+12*21+12,  "SpritePalette021","data/graphics/sprites/palettes/spritepalette021.bin",file);
    splitSingleChunk(0x1A47E0+12*22,  0x1A47E0+12*22+12,  "SpritePalette022","data/graphics/sprites/palettes/spritepalette022.bin",file);
    splitSingleChunk(0x1A47E0+12*23,  0x1A47E0+12*23+12,  "SpritePalette023","data/graphics/sprites/palettes/spritepalette023.bin",file);
    splitSingleChunk(0x1A47E0+12*24,  0x1A47E0+12*24+12,  "SpritePalette024","data/graphics/sprites/palettes/spritepalette024.bin",file);
    splitSingleChunk(0x1A47E0+12*25,  0x1A47E0+12*25+12,  "SpritePalette025","data/graphics/sprites/palettes/spritepalette025.bin",file);
    splitSingleChunk(0x1A47E0+12*26,  0x1A47E0+12*26+12,  "SpritePalette026","data/graphics/sprites/palettes/spritepalette026.bin",file);
    splitSingleChunk(0x1A47E0+12*27,  0x1A47E0+12*27+12,  "SpritePalette027","data/graphics/sprites/palettes/spritepalette027.bin",file);
    splitSingleChunk(0x1A47E0+12*28,  0x1A47E0+12*28+12,  "SpritePalette028","data/graphics/sprites/palettes/spritepalette028.bin",file);
    splitSingleChunk(0x1A47E0+12*29,  0x1A47E0+12*29+12,  "SpritePalette029","data/graphics/sprites/palettes/spritepalette029.bin",file);
    splitSingleChunk(0x1A47E0+12*30,  0x1A47E0+12*30+12,  "SpritePalette030","data/graphics/sprites/palettes/spritepalette030.bin",file);
    splitSingleChunk(0x1A47E0+12*31,  0x1A47E0+12*31+12,  "SpritePalette031","data/graphics/sprites/palettes/spritepalette031.bin",file);
    splitSingleChunk(0x1A47E0+12*32,  0x1A47E0+12*32+12,  "SpritePalette032","data/graphics/sprites/palettes/spritepalette032.bin",file);
    splitSingleChunk(0x1A47E0+12*33,  0x1A47E0+12*33+12,  "SpritePalette033","data/graphics/sprites/palettes/spritepalette033.bin",file);
    splitSingleChunk(0x1A47E0+12*34,  0x1A47E0+12*34+12,  "SpritePalette034","data/graphics/sprites/palettes/spritepalette034.bin",file);
    splitSingleChunk(0x1A47E0+12*35,  0x1A47E0+12*35+12,  "SpritePalette035","data/graphics/sprites/palettes/spritepalette035.bin",file);
    splitSingleChunk(0x1A47E0+12*36,  0x1A47E0+12*36+12,  "SpritePalette036","data/graphics/sprites/palettes/spritepalette036.bin",file);
    splitSingleChunk(0x1A47E0+12*37,  0x1A47E0+12*37+12,  "SpritePalette037","data/graphics/sprites/palettes/spritepalette037.bin",file);
    splitSingleChunk(0x1A47E0+12*38,  0x1A47E0+12*38+12,  "SpritePalette038","data/graphics/sprites/palettes/spritepalette038.bin",file);
    splitSingleChunk(0x1A47E0+12*39,  0x1A47E0+12*39+12,  "SpritePalette039","data/graphics/sprites/palettes/spritepalette039.bin",file);
    splitSingleChunk(0x1A47E0+12*40,  0x1A47E0+12*40+12,  "SpritePalette040","data/graphics/sprites/palettes/spritepalette040.bin",file);
    splitSingleChunk(0x1A47E0+12*41,  0x1A47E0+12*41+12,  "SpritePalette041","data/graphics/sprites/palettes/spritepalette041.bin",file);
    splitSingleChunk(0x1A47E0+12*42,  0x1A47E0+12*42+12,  "SpritePalette042","data/graphics/sprites/palettes/spritepalette042.bin",file);
    splitSingleChunk(0x1A47E0+12*43,  0x1A47E0+12*43+12,  "SpritePalette043","data/graphics/sprites/palettes/spritepalette043.bin",file);
    splitSingleChunk(0x1A47E0+12*44,  0x1A47E0+12*44+12,  "SpritePalette044","data/graphics/sprites/palettes/spritepalette044.bin",file);
    splitSingleChunk(0x1A47E0+12*45,  0x1A47E0+12*45+12,  "SpritePalette045","data/graphics/sprites/palettes/spritepalette045.bin",file);
    splitSingleChunk(0x1A47E0+12*46,  0x1A47E0+12*46+12,  "SpritePalette046","data/graphics/sprites/palettes/spritepalette046.bin",file);
    splitSingleChunk(0x1A47E0+12*47,  0x1A47E0+12*47+12,  "SpritePalette047","data/graphics/sprites/palettes/spritepalette047.bin",file);
    splitSingleChunk(0x1A47E0+12*48,  0x1A47E0+12*48+12,  "SpritePalette048","data/graphics/sprites/palettes/spritepalette048.bin",file);
    splitSingleChunk(0x1A47E0+12*49,  0x1A47E0+12*49+12,  "SpritePalette049","data/graphics/sprites/palettes/spritepalette049.bin",file);
    splitSingleChunk(0x1A47E0+12*50,  0x1A47E0+12*50+12,  "SpritePalette050","data/graphics/sprites/palettes/spritepalette050.bin",file);
    splitSingleChunk(0x1A47E0+12*51,  0x1A47E0+12*51+12,  "SpritePalette051","data/graphics/sprites/palettes/spritepalette051.bin",file);
    splitSingleChunk(0x1A47E0+12*52,  0x1A47E0+12*52+12,  "SpritePalette052","data/graphics/sprites/palettes/spritepalette052.bin",file);
    splitSingleChunk(0x1A47E0+12*53,  0x1A47E0+12*53+12,  "SpritePalette053","data/graphics/sprites/palettes/spritepalette053.bin",file);
    splitSingleChunk(0x1A47E0+12*54,  0x1A47E0+12*54+12,  "SpritePalette054","data/graphics/sprites/palettes/spritepalette054.bin",file);
    splitSingleChunk(0x1A47E0+12*55,  0x1A47E0+12*55+12,  "SpritePalette055","data/graphics/sprites/palettes/spritepalette055.bin",file);
    splitSingleChunk(0x1A47E0+12*56,  0x1A47E0+12*56+12,  "SpritePalette056","data/graphics/sprites/palettes/spritepalette056.bin",file);
    splitSingleChunk(0x1A47E0+12*57,  0x1A47E0+12*57+12,  "SpritePalette057","data/graphics/sprites/palettes/spritepalette057.bin",file);
    splitSingleChunk(0x1A47E0+12*58,  0x1A47E0+12*58+12,  "SpritePalette058","data/graphics/sprites/palettes/spritepalette058.bin",file);
    splitSingleChunk(0x1A47E0+12*59,  0x1A47E0+12*59+12,  "SpritePalette059","data/graphics/sprites/palettes/spritepalette059.bin",file);
    splitSingleChunk(0x1A47E0+12*60,  0x1A47E0+12*60+12,  "SpritePalette060","data/graphics/sprites/palettes/spritepalette060.bin",file);
    splitSingleChunk(0x1A47E0+12*61,  0x1A47E0+12*61+12,  "SpritePalette061","data/graphics/sprites/palettes/spritepalette061.bin",file);
    splitSingleChunk(0x1A47E0+12*62,  0x1A47E0+12*62+12,  "SpritePalette062","data/graphics/sprites/palettes/spritepalette062.bin",file);
    splitSingleChunk(0x1A47E0+12*63,  0x1A47E0+12*63+12,  "SpritePalette063","data/graphics/sprites/palettes/spritepalette063.bin",file);
    splitSingleChunk(0x1A47E0+12*64,  0x1A47E0+12*64+12,  "SpritePalette064","data/graphics/sprites/palettes/spritepalette064.bin",file);
    splitSingleChunk(0x1A47E0+12*65,  0x1A47E0+12*65+12,  "SpritePalette065","data/graphics/sprites/palettes/spritepalette065.bin",file);
    splitSingleChunk(0x1A47E0+12*66,  0x1A47E0+12*66+12,  "SpritePalette066","data/graphics/sprites/palettes/spritepalette066.bin",file);
    splitSingleChunk(0x1A47E0+12*67,  0x1A47E0+12*67+12,  "SpritePalette067","data/graphics/sprites/palettes/spritepalette067.bin",file);
    splitSingleChunk(0x1A47E0+12*68,  0x1A47E0+12*68+12,  "SpritePalette068","data/graphics/sprites/palettes/spritepalette068.bin",file);
    splitSingleChunk(0x1A47E0+12*69,  0x1A47E0+12*69+12,  "SpritePalette069","data/graphics/sprites/palettes/spritepalette069.bin",file);
    splitSingleChunk(0x1A47E0+12*70,  0x1A47E0+12*70+12,  "SpritePalette070","data/graphics/sprites/palettes/spritepalette070.bin",file);
    splitSingleChunk(0x1A47E0+12*71,  0x1A47E0+12*71+12,  "SpritePalette071","data/graphics/sprites/palettes/spritepalette071.bin",file);
    splitSingleChunk(0x1A47E0+12*72,  0x1A47E0+12*72+12,  "SpritePalette072","data/graphics/sprites/palettes/spritepalette072.bin",file);
    splitSingleChunk(0x1A47E0+12*73,  0x1A47E0+12*73+12,  "SpritePalette073","data/graphics/sprites/palettes/spritepalette073.bin",file);
    splitSingleChunk(0x1A47E0+12*74,  0x1A47E0+12*74+12,  "SpritePalette074","data/graphics/sprites/palettes/spritepalette074.bin",file);
    splitSingleChunk(0x1A47E0+12*75,  0x1A47E0+12*75+12,  "SpritePalette075","data/graphics/sprites/palettes/spritepalette075.bin",file);
    splitSingleChunk(0x1A47E0+12*76,  0x1A47E0+12*76+12,  "SpritePalette076","data/graphics/sprites/palettes/spritepalette076.bin",file);
    splitSingleChunk(0x1A47E0+12*77,  0x1A47E0+12*77+12,  "SpritePalette077","data/graphics/sprites/palettes/spritepalette077.bin",file);
    splitSingleChunk(0x1A47E0+12*78,  0x1A47E0+12*78+12,  "SpritePalette078","data/graphics/sprites/palettes/spritepalette078.bin",file);
    splitSingleChunk(0x1A47E0+12*79,  0x1A47E0+12*79+12,  "SpritePalette079","data/graphics/sprites/palettes/spritepalette079.bin",file);
    splitSingleChunk(0x1A4BA0+14*0,   0x1A4BA0+14*0+14,   "SpritePalette128","data/graphics/sprites/palettes/spritepalette128.bin",file);
    splitSingleChunk(0x1A4BA0+14*1,   0x1A4BA0+14*1+14,   "SpritePalette129","data/graphics/sprites/palettes/spritepalette129.bin",file);
    splitSingleChunk(0x1A4BA0+14*2,   0x1A4BA0+14*2+14,   "SpritePalette130","data/graphics/sprites/palettes/spritepalette130.bin",file);
    splitSingleChunk(0x1A4BA0+14*3,   0x1A4BA0+14*3+14,   "SpritePalette131","data/graphics/sprites/palettes/spritepalette131.bin",file);
    splitSingleChunk(0x1A4BA0+14*4,   0x1A4BA0+14*4+14,   "SpritePalette132","data/graphics/sprites/palettes/spritepalette132.bin",file);
    splitSingleChunk(0x1A4BA0+14*5,   0x1A4BA0+14*5+14,   "SpritePalette133","data/graphics/sprites/palettes/spritepalette133.bin",file);
    splitSingleChunk(0x1A4BA0+14*6,   0x1A4BA0+14*6+14,   "SpritePalette134","data/graphics/sprites/palettes/spritepalette134.bin",file);
    splitSingleChunk(0x1A4BA0+14*7,   0x1A4BA0+14*7+14,   "SpritePalette135","data/graphics/sprites/palettes/spritepalette135.bin",file);
    splitSingleChunk(0x1A4BA0+14*8,   0x1A4BA0+14*8+14,   "SpritePalette136","data/graphics/sprites/palettes/spritepalette136.bin",file);
    splitSingleChunk(0x1A4BA0+14*9,   0x1A4BA0+14*9+14,   "SpritePalette137","data/graphics/sprites/palettes/spritepalette137.bin",file);
    splitSingleChunk(0x1A4BA0+14*10,  0x1A4BA0+14*10+14,  "SpritePalette138","data/graphics/sprites/palettes/spritepalette138.bin",file);
    splitSingleChunk(0x1A4BA0+14*11,  0x1A4BA0+14*11+14,  "SpritePalette139","data/graphics/sprites/palettes/spritepalette139.bin",file);
    splitSingleChunk(0x1A4BA0+14*12,  0x1A4BA0+14*12+14,  "SpritePalette140","data/graphics/sprites/palettes/spritepalette140.bin",file);
    splitSingleChunk(0x1A4BA0+14*13,  0x1A4BA0+14*13+14,  "SpritePalette141","data/graphics/sprites/palettes/spritepalette141.bin",file);
    splitSingleChunk(0x1A4BA0+14*14,  0x1A4BA0+14*14+14,  "SpritePalette142","data/graphics/sprites/palettes/spritepalette142.bin",file);
    splitSingleChunk(0x1A4BA0+14*15,  0x1A4BA0+14*15+14,  "SpritePalette143","data/graphics/sprites/palettes/spritepalette143.bin",file);
    splitSingleChunk(0x1A4BA0+14*16,  0x1A4BA0+14*16+14,  "SpritePalette144","data/graphics/sprites/palettes/spritepalette144.bin",file);

    
    splitSingleChunk(0x1E0000, 0x1E8000, "PCMBank0","data/sound/pcmbank0.bin",file);
    splitSingleChunk(0x1E8000, 0x1F0000, "PCMBank1","data/sound/pcmbank1.bin",file);
    splitSingleChunk(0x1F0000, 0x1F6000, "MusibBank0","data/sound/musicbank0build.bin",file);
    splitSingleChunk(0x1F6000, 0x1F8000, "SoundDriver","data/sound/sounddriver.bin",file);
    splitSingleChunk(0x1F8000, 0x1F8910, "YMInstruments","data/sound/yminst.bin",file);
    splitSingleChunk(0x1F8000, 0x200000, "MusicBank1","data/sound/musicbank1build.bin",file);

    
}

static splitSingleChunk(start, end, nameString, binPath, splitFile){
    splitSingleChunkWithConditionalIncbin(start, end, nameString, binPath, splitFile, 0);
}

static splitSingleChunkWithConditionalIncbin(start, end, nameString, binPath, splitFile, incbinType){
    auto j,incbin;
    //Message("Cleaning from %a to %a ...\n",start,end);
    for(j=start+1;j<end;j++){undefineByte(j);}
    MakeData(start,FF_BYTE,end-start,1);
    if(nameString!=""){
        MakeNameEx(start,nameString,0);
    }
    if(incbinType==1){
        incbin = "incbinIfVanillaRom";
    }else{
        incbin = "incbin";
    }
    SetManualInsn   (start, form("%s \"%s\"",incbin,binPath));
    writestr(splitFile,form("#split\t0x%s,0x%s,%s\n",ltoa(start,16),ltoa(end,16),binPath));
    //Jump(start);
}

static splitSingleChunkWithCommentedSplitEntry(start, end, nameString, binPath, splitFile){
    auto j;
    //Message("Cleaning from %a to %a ...\n",start,end);
    for(j=start+1;j<end;j++){undefineByte(j);}
    MakeData(start,FF_BYTE,end-start,1);
    MakeNameEx(start,nameString,0);
    SetManualInsn   (start, form("incbin \"%s\"",binPath));
    writestr(splitFile,form("/*#split\t0x%s,0x%s,%s*/\n",ltoa(start,16),ltoa(end,16),binPath));
    //Jump(start);
}


/*
 *  Split one simple pointer table
 */
static splitPT(start, end, lastEntryDataEnd, chunkEnd, ptName, entryName, binDir, entryDirs, binName, indexLength, align, file) {
    auto i,j,x,s,index,path;
    auto addr,dataEnd,from,dref,section,action;
    auto binDirIndex,binNameIndex;
    i = 0;
    addr = start;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        MakeNameExC(dref,form("%s%s",entryName,index),0);
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<chunkEnd){
                    dataEnd = j;
                }
          from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    // Put align instruction for padding until chunkEnd
    if(align!=0)MakeAlign(lastEntryDataEnd,chunkEnd-lastEntryDataEnd,align);
}



static splitSprites(file) {
    auto i,j,k,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,binDirIndex,binNameIndex,ptName,binDir,entryDirs,binName,indexLength,align,entryName, subEntryName;
    auto facingId;
    auto subStart, subEnd, subIndex, subAddr, currentEntryName;
    i = 0;
    start = 0x1201B4;
    end = 0x120800;
    subStart = 0x120800;
    subEnd = 0x121BD0;
    addr = start;
    lastEntryDataEnd = 0x1A42DE;
    chunkEnd = 0x1A42DE;
    ptName = "pt_Sprites";
    entryName = "Sprite";
    subEntryName = "SpriteFrame";
    binDir = "data/graphics/sprites/";
    entryDirs = 0;
    binName = "sprite";
    indexLength = 3;
    align = 15;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        currentEntryName = form("%s%s",entryName,index);
        MakeNameExC(dref,currentEntryName,0);
        addr=addr+4;
        i++;
    }
    addr = start;
    i = 0;
    while(addr<end&&action==1){
        dref = Dfirst(addr);     
        index = ltoa(i,10);
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        currentEntryName = form("%s%s",entryName,index);
        subAddr = dref;
        j=0;
        while(GetTrueName(subAddr)==form("%s%s",entryName,index) || GetTrueName(subAddr)==""){
	        MakeDword(subAddr);
	        dref = Dword(subAddr);
	        add_dref(subAddr,dref,dr_O);
	        dref = Dfirst(subAddr);    
	        MakeNameExC(dref,form("%s%sFrame%s",entryName,index,ltoa(j,10)),0);
	        j++;
	        subAddr = subAddr+4;
        }
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */

    addr = start;
    i = 0;
    while(addr<end&&action==1){
        dref = Dfirst(addr);     
        index = ltoa(i,10);
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        currentEntryName = form("%s%s",entryName,index);
        subAddr = dref;
        k=0;
        while(GetTrueName(subAddr)==form("%s%s",entryName,index) || GetTrueName(subAddr)==""){
	        dref = Dfirst(subAddr);    
	               
            //Jump(dref); 
            dataEnd = 0;
            j = dref+1;
            // Finding entry's data end
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            index = ltoa(i,10);
            while(strlen(index)<indexLength){
                index=form("0%s",index);
            }
            //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
            MakeData(dref,FF_BYTE,dataEnd-dref,1);
            if(strstr(GetDisasm(dref),"incbin")==-1){    
                if(entryDirs==0){
                    binDirIndex = "";
                    binNameIndex = index;
                } else{
                    binDirIndex = index;
                    binNameIndex = "";
                }
                SetManualInsn   (dref, form("incbin \"%s%s%s%sframe%s.bin\"",binDir,binDirIndex,binName,binNameIndex,ltoa(k,10)));
                writestr(file,form("#split\t0x%s,0x%s,%s%s%s%sframe%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex,ltoa(k,10)));
            }
            //action = AskYN(1,"Ok ?");
        
	        k++;
	        subAddr = subAddr+4;
        }
        addr=addr+4;
        i++;
    }     
    // Put align instruction for padding until chunkEnd
    if(align!=0)MakeAlign(lastEntryDataEnd,chunkEnd-lastEntryDataEnd,align);
}




static splitMaps(file) {
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,binDirIndex,binNameIndex,ptName,binDir,entryDirs,binName,indexLength,align,entryName;
    auto facingId;
    i = 0;
    start = 0xA0A12;
    end = 0xA2392;
    addr = start;
    lastEntryDataEnd = 0x11C926;
    entryName = "Map";
    ptName = "pt_Maps";
    binDir = "data/maps/entries/map";
    entryDirs = 1;
    binName = "data";
    indexLength = 3;
    align = 15;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<lastEntryDataEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);}        
        MakeNameExC(dref,form("%s%s",entryName,index),0);
        MakeByte(addr+4);
        MakeByte(addr+5);
        MakeByte(addr+6);
        MakeByte(addr+7);
        addr=addr+8;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){
                    dataEnd = j;
                }
                from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);} 
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s/%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s/%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+8;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){
                    dataEnd = j;
                }
                from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+8;
        i++;
        //action = AskYN(1,"Ok ?");
    }
}


static splitMapTilesets(file) {
    auto i,j,x,s,index,path;
    auto start,end,firstEntryDataStart,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,binDirIndex,binNameIndex,ptName,binDir,entryDirs,binName,indexLength,align,entryName;
    auto facingId;
    i = 0;
    start = 0x44070;
    end = 0x440B8;
    addr = start;
    firstEntryDataStart = 0x440F0;
    lastEntryDataEnd = 0x94F2A;
    entryName = "MapTileset";
    ptName = "pt_MapTilesets";
    binDir = "data/graphics/maps/tilesets/";
    entryDirs = 0;
    binName = "maptileset";
    indexLength = 2;
    align = 15;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<end;j++){undefineByte(j);}
    for(j=firstEntryDataStart;j<lastEntryDataEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);}        
        MakeNameExC(dref,form("%s%s",entryName,index),0);
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){
                    dataEnd = j;
                }
                from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);} 
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s/%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s/%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){
                    dataEnd = j;
                }
                from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
}

static splitAnimatedMapTilesets(file) {
    auto i,j,x,s,index,path;
    auto start,end,firstEntryDataStart,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,binDirIndex,binNameIndex,ptName,binDir,entryDirs,binName,indexLength,align,entryName;
    auto facingId;
    i = 0;
    start = 0x44014;
    end = 0x4406C;
    addr = start;
    firstEntryDataStart = 0x94F2A;
    lastEntryDataEnd = 0x9A4EA;
    entryName = "AnimatedMapTileset";
    binDir = "data/graphics/maps/tilesets/animated/";
    entryDirs = 0;
    binName = "animatedmaptileset";
    indexLength = 2;
    align = 15;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<end;j++){undefineByte(j);}
    for(j=firstEntryDataStart;j<lastEntryDataEnd;j++){undefineByte(j);}
    // Naming pointer table
    //MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);}        
        MakeNameExC(dref,form("%s%s",entryName,index),0);
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){
                    dataEnd = j;
                }
                from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);} 
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s/%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s/%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){
                    dataEnd = j;
                }
                from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
}



static splitMapBlocks(file) {
    auto i,j,k,x,s,index,subindex,path;
    auto start,end,firstEntryDataStart,lastEntryDataEnd,subptstart,subptend,subptaddr,chunkEnd,addr,dataEnd,from,dref,section,action,binDirIndex,binNameIndex,ptName,binDir,entryDirs,binName,indexLength,align,entryName;
    auto facingId;
    i = 0;
    start = 0x1AF804;
    end = 0x1AF8C8;
    addr = start;
    subptstart = 0x1AF904;
    subptend = 0x1AFAD0;
    firstEntryDataStart = 0x1AFAD0;
    lastEntryDataEnd = 0x1DF9F8;
    entryName = "MapBlock";
    ptName = "pt_MapBlocks";
    binDir = "data/graphics/maps/blocks";
    entryDirs = 0;
    binName = "mapblock";
    indexLength = 2;
    align = 15;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<end;j++){undefineByte(j);}
    for(j=subptstart;j<subptend;j++){undefineByte(j);}
    for(j=firstEntryDataStart;j<lastEntryDataEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);}        
        MakeNameExC(dref,form("%s%s",entryName,index),0);
        addr=addr+4;
        i++;
    }
    i = 0;
    subindex=0;
    addr = start;
    while(addr<end&&action==1){
        dref = Dword(addr);   
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);} 
        j=0;
        subptaddr = dref;
        while(subptaddr==dref||GetTrueName(subptaddr)==""){ 
          MakeDword(subptaddr);
          dref = Dword(subptaddr);
          add_dref(subptaddr,dref,dr_O);
          dref = Dfirst(subptaddr);     
          subindex = ltoa(j,10);
          while(strlen(subindex)<indexLength){subindex=form("0%s",subindex);}        
          MakeNameExC(dref,form("%s%s_%s",entryName,index,subindex),0);
          MakeByte(dref);
          subptaddr=subptaddr+4;
          j++;
        }
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    subindex=0;
    addr = start;
    while(addr<end&&action==1){
        dref = Dword(addr);   
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index=form("0%s",index);} 
        j=0;
        subptaddr = dref;
        while(subptaddr==dref||GetTrueName(subptaddr)==""){ 
          dref = Dword(subptaddr);   
          subindex = ltoa(j,10);
          while(strlen(subindex)<indexLength){subindex=form("0%s",subindex);}
          dataEnd = 0;
          k = dref+1;
          // Finding entry's data end
          while(dataEnd==0){
              k++;
              if(GetTrueName(k)!="") dataEnd = k;
              if(k==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
          }
          index = ltoa(i,10);
          while(strlen(index)<indexLength){index=form("0%s",index);} 
          //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
          MakeData(dref,FF_BYTE,dataEnd-dref,1);
          if(strstr(GetDisasm(dref),"incbin")==-1){    
              if(entryDirs==0){
                  binDirIndex = "";
                  binNameIndex = index;
              } else{
                  binDirIndex = index;
                  binNameIndex = "";
              }
              SetManualInsn   (dref, form("incbin \"%s%s/%s%s-%s.bin\"",binDir,binDirIndex,binName,binNameIndex,subindex));
              writestr(file,form("#split\t0x%s,0x%s,%s%s/%s%s-%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex,subindex));
          }
          subptaddr=subptaddr+4;
          j++;
        }
        addr=addr+4;
        i++;
    }
}

/* SF2 examples */

static splitMapsprites(file) {
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,binDirIndex,binNameIndex,ptName,binDir,entryDirs,binName,indexLength,align,entryName;
    auto facingId;
    i = 0;
    start = 0xC8000;
    end = 0xC8B40;
    addr = start;
    lastEntryDataEnd = 0xFFC48;
    chunkEnd = 0x100000;
    ptName = "pt_MapSprites";
    entryName = "MapSprite";
    binDir = "data/graphics/mapsprites/";
    entryDirs = 0;
    binName = "mapsprite";
    indexLength = 3;
    align = 15;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i/3,10);
        facingId = i%3;
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        MakeNameExC(dref,form("%s%s_%d",entryName,index,facingId),0);
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<chunkEnd){
                    dataEnd = j;
                }
          from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i/3,10);
        facingId = i%3;
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        index = form("%s-%d",index,facingId);
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    // Put align instruction for padding until chunkEnd
    if(align!=0)MakeAlign(lastEntryDataEnd,chunkEnd-lastEntryDataEnd,align);
}

static splitMapsSF2(file) {
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,sectionNamesForFiles,sectionNamesForLabels,currentSectionName;
    i = 0;
    start = 0x94B8A;
    end = 0x94CC6;
    addr = start;
    lastEntryDataEnd = 0xC7ECC;
    chunkEnd = 0xC8000;
    action=1;
    sectionNamesForFiles="0=blocks;1=layout;2=areas;3=flag-events;4=step-events;5=roof-events;6=warp-events;7=chest-items;8=other-items;9=animations;10";
    sectionNamesForLabels="0=Blocks;1=Layout;2=Areas;3=FlagEvents;4=StepEvents;5=RoofEvents;6=WarpEvents;7=ChestItems;8=OtherItems;9=Animations;10";
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);    
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    MakeNameEx(addr,"pt_MapData",0);
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        MakeNameEx(dref,form("Map%s",index),0);
        //writestr(file,form("#dir\tdata/maps/entries/map%s\n",index));
                MakeData(dref,FF_BYTE,0x6,0);
                /*if(strstr(GetDisasm(dref),"incbin")==-1){    
                    SetManualInsn(dref, form("incbin \"data/maps/entries/map%s/00-tilesets.bin\"",index));
                    writestr(file,form("#split\t0x%s,0x%s,data/maps/entries/map%s/00-tilesets.bin\n",ltoa(dref,16),ltoa(dref+6,16),index));
                }    */    
                //Message(form("\nproduceAsmScript(file,\"data\\\\maps\\\\entries\\\\map%s\\\\00-tilesets.asm\",0x%s,0x%s,\"\");",index,ltoa(dref,16),ltoa(dref+6,16)));
        for(s=0;s!=10;s++){
            from = dref+6+4*s;
            MakeDword(from);
            section = Dword(from);
            add_dref(from,section,dr_O);
            currentSectionName = substr(sectionNamesForLabels,strstr(sectionNamesForLabels,form("%d",s))+2,strstr(sectionNamesForLabels,form("%d",s+1))-1);
            MakeNameExC(section,form("Map%ss%d_%s",index,s,currentSectionName),0);
        } 
        addr=addr+4;
        i++;
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        //Message(form("\nproduceAsmScript(file,\"data\\\\maps\\\\entries\\\\map%s\\\\00-tilesets.asm\",0x%s,0x%s,\"\");",index,ltoa(dref,16),ltoa(dref+6,16)));
        //Message(form("\nproduceAsmSection(file,0x%s,0x%s);",ltoa(dref+6,16),ltoa(dref+6+10*4,16)));
        for(s=0;s!=10;s++){
            section = Dfirst(dref+6+4*s);
            if(section!=BADADDR){
                dataEnd = 0;
                j = section+1;
                while(dataEnd==0){
                    from = DfirstB(j);
                    while(from!=BADADDR){
                        if(from>=start&&from<chunkEnd){
                            dataEnd = j;
                        }
                  from=DnextB(addr,from);      
                    }
                    j++;
                    if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
                }
                currentSectionName = substr(sectionNamesForFiles,strstr(sectionNamesForFiles,form("%d",s))+2,strstr(sectionNamesForFiles,form("%d",s+1))-1);
                //Message(form("Processing Map%s section%d at %s, dataEnd %s\n",index,s,ltoa(section,16),ltoa(dataEnd,16)));
                MakeData(section,FF_BYTE,dataEnd-section,1);
                if(strstr(GetDisasm(section),"incbin")==-1){    
                    if(s<2){
                        SetManualInsn(section, form("incbin \"data/maps/entries/map%s/%s-%s.bin\"",index,ltoa(s,10),currentSectionName));
                        writestr(file,form("#split\t0x%s,0x%s,data/maps/entries/map%s/%s-%s.bin\n",ltoa(section,16),ltoa(dataEnd,16),index,ltoa(s,10),currentSectionName));
                        //Message(form("\nproduceAsmSection(file,0x%s,0x%s);",ltoa(section,16),ltoa(dataEnd,16)));
                    }else{
                        SetManualInsn(section, "");
                        //Message(form("\nproduceAsmScript(file,\"data\\\\maps\\\\entries\\\\map%s\\\\%s-%s.asm\",0x%s,0x%s,\"\");",index,ltoa(s,10),currentSectionName,ltoa(section,16),ltoa(dataEnd,16)));
                    }
                }
            }
        }
        //Message("\n");
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    MakeAlign(lastEntryDataEnd, chunkEnd-lastEntryDataEnd,15);
}


static splitGrounds(file) {

    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,base,dataEnd,from,dref,section,action;
    i = 0;
    start = 0x1B8028;
    end = 0x1B80A0;
    addr = start;
    lastEntryDataEnd = 0x1B9A9A;
    chunkEnd = 0x1B9A9A;
    action=1;
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);    
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    MakeNameExC(addr,"pt_Grounds",0);
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        if(strstr(GetTrueName(dref),"Ground")==-1){
            index = ltoa(i,10);
            if(strlen(index)==1)index=form("0%s",index);
            MakeNameExC(dref,form("Ground%s",index),0);
            /*MakeData(dref, FF_WORD, 0x2, 0);
            MakeData(dref+2, FF_WORD, 0x2, 0);
            MakeData(dref+4, FF_WORD, 0x2, 0);*/
            splitSingleChunk(dref, dref+6, "", form("data/graphics/battles/grounds/groundpalette%s.bin",index),file);        
            MakeData(dref+6, FF_WORD, 0x2, 0);
            MakeNameExC(dref+6,form("bsg%s_rpbase",index),0);
            base = dref+6;
            OpOffEx(base, -1, REF_OFF32, -1, base, 0);
            section = Word(base) + base;
            add_dref(base,section,dr_O);
            //Message("base %a, section %a\n",base, section);
            MakeNameExC(section,form("GroundTiles%s",index),0);        
        }
        addr=addr+4;
        i++;
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);
        base = dref+6;
        dref = Word(base) + base;    
        //Jump(dref); 
                dataEnd = 0;
                j = dref+1;
                while(dataEnd==0){
                    from = DfirstB(j);
                    while(from!=BADADDR){
                        if(from>=start&&from<chunkEnd){
                            dataEnd = j;
                        }
                  from=DnextB(addr,from);      
                    }
                    j++;
                    if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
                }
                index = ltoa(i,10);
                if(strlen(index)==1)index=form("0%s",index);
                //Message(form("Processing ground%s at %s, dataEnd %s\n",index,ltoa(dref,16),ltoa(dataEnd,16)));
                MakeData(dref,FF_BYTE,dataEnd-dref,1);
                if(strstr(GetDisasm(dref),"incbin")==-1){
                    SetManualInsn   (dref, form("incbin \"data/graphics/battles/grounds/groundtiles%s.bin\"",index));
                    writestr(file,form("#split\t0x%s,0x%s,data/graphics/battles/grounds/groundtiles%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
                }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }

}

static splitTextbanks(file) {
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action;
    i = 0;
    start = 0x41FDA;
    end = 0x4201E;
    addr = start;
    lastEntryDataEnd = 0x41FD9;
    chunkEnd = 0x4201E;
    action=1;
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);        
    for(j=0x2EB34;j<chunkEnd;j++){undefineByte(j);}
    MakeNameEx(addr,"pt_TextBanks",0);
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        MakeNameEx(dref,form("TextBank%s",index),0);
        addr=addr+4;
        i++;
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<chunkEnd){
                    dataEnd = j;
                }
          from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        //Message(form("dref %s, dataEnd %s\n",ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        SetManualInsn   (dref, form("incbin \"data/scripting/text/textbank%s.bin\"",index));
        writestr(file,form("#split\t0x%s,0x%s,data/scripting/text/textbank%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    MakeAlign(0x41FD9, 0x41FDA-0x41FD9,1);
}



static MakeNameExC(addr,name,flags){

    auto current;
    current = GetTrueName(addr);
    if(current=="" || strstr(current,"unk_")!=-1 || strstr(current,"byte_")!=-1 || strstr(current,"word_")!=-1 || strstr(current,"dword_")!=-1 || strstr(current,"off_")!=-1){
        MakeNameEx(addr,name,flags);
    }

}




/* 
 *  Makes sure byte at addr is
 *  clean for new formatting
 */
static undefineByte(addr){
        auto from;
        from = DfirstB(addr);
        while(from!=BADADDR){
            //Message(form("Removed DATA XRef at addr %a, from %a\n",addr, from));
      del_dref(from,addr);
      from=DnextB(addr,from);
        }        
        from = RfirstB(addr);
        while(from!=BADADDR){
            //Message(form("Removed Code XRrf at addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
        }                
        MakeUnkn(addr,DOUNK_DELNAMES);
        MakeNameEx(addr,"",0);
        SetManualInsn(addr,"");
}




