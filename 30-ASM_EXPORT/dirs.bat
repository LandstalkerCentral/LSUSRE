mkdir disasm
mkdir disasm\layout
mkdir disasm\code
mkdir disasm\code\gameflow
mkdir disasm\code\gameflow\start
mkdir disasm\code\common
mkdir disasm\code\common\tech
mkdir disasm\code\common\tech\interrupts
mkdir disasm\code\common\tech\sram
mkdir disasm\code\common\tech\sound
mkdir disasm\code\common\tech\graphics
mkdir disasm\code\common\maps
mkdir disasm\code\common\stats
mkdir disasm\code\common\stats\items
mkdir disasm\code\common\menus\
mkdir disasm\code\common\scripting
mkdir disasm\code\common\scripting\text
mkdir disasm\code\specialscreens
mkdir disasm\code\specialscreens\segalogo
mkdir disasm\code\specialscreens\title
mkdir disasm\code\specialscreens\saves
mkdir disasm\data
mkdir disasm\data\maps
mkdir disasm\data\maps\global
mkdir disasm\data\maps\entries
FOR /L %%G IN (0,1,9) DO mkdir disasm\data\maps\entries\map00%%G
FOR /L %%G IN (10,1,99) DO mkdir disasm\data\maps\entries\map0%%G
FOR /L %%G IN (100,1,816) DO mkdir disasm\data\maps\entries\map%%G
mkdir disasm\data\scripting
mkdir disasm\data\scripting\text
mkdir disasm\data\scripting\text\intro
mkdir disasm\data\sound
mkdir disasm\data\sound\musicbank0
mkdir disasm\data\sound\musicbank1
mkdir disasm\data\graphics
mkdir disasm\data\graphics\sprites\
mkdir disasm\data\graphics\sprites\palettes\
mkdir disasm\data\graphics\maps
mkdir disasm\data\graphics\maps\palettes
mkdir disasm\data\graphics\maps\tilesets
mkdir disasm\data\graphics\maps\tilesets\animated
mkdir disasm\data\graphics\maps\blocks
pause