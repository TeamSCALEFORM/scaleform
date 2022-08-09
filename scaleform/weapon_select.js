R"(
var hws = contextPanel.FindChildTraverse('HudWeaponSelection');

for (select of hws.FindChildrenWithClassTraverse("weapon-selection-item")) {
    select.style.transform = 'translateY(0px)';
    select.style.marginTop = '3px';
    select.style.overflow = 'noclip';
    select.style.verticalAlign = 'center';
    for (text of select.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
        text.style.fontSize = '17px';
        text.style.fontFamily = 'Stratum2';
        text.style.transform = 'translateY(-5px) translateX(5px)';
        text.style.fontWeight = 'bold';
    }
    for (icon of select.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
        icon.style.imgShadow = '#00000000 0px 0px 0px 0';
        icon.style.marginBottom = '5px';
        icon.style.marginRight = '8px';
        icon.style.marginLeft = '12px';
        icon.style.padding = '5px';
    }
}

for (row of hws.FindChildrenWithClassTraverse('weapon-row')) {
//    if (row.BHasClass('weapon-row--selected')) 
{
        for(test of row.FindChildrenWithClassTraverse('weapon-row-background'))
        {
            test.style.backgroundImage = 'url("https://cdn.discordapp.com/attachments/808866622701830186/1001890355169476669/weapon_row_bg.png")';
            test.style.backgroundRepeat = 'no-repeat'
            test.style.backgroundPosition = 'right';
            test.style.backgroundSize = '221px 83px'
            test.style.horizontalAlign = 'right';
            test.style.backgroundImgOpacity = '0.7';
        }
}
}
for (rowNumber of hws.FindChildrenWithClassTraverse('weapon-row-number')) {
    rowNumber.style.fontSize = '16px';
    rowNumber.style.fontWeight = 'bold';
    rowNumber.style.transform = 'translateY(-5px)';
}
)"