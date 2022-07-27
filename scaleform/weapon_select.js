R"weapsel(
function runner() {


    var contextPanel = $.GetContextPanel();
    
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

    for (var row of hws.FindChildrenWithClassTraverse('weapon-row')) {
        if (row.BHasClass('weapon-row--selected')) {
            row.style.overflow = 'squish';
            row.style.width = '221px';
            row.style.height = '83px';
            row.style.backgroundImage = 'url("https://cdn.discordapp.com/attachments/808866622701830186/1001890355169476669/weapon_row_bg.png")';
            row.style.backgroundColor = '#00000000';
            row.style.backgroundSize = 'cover';
            row.style.backgroundImgOpacity = '0.7';
            row.style.transform = 'translateX(1px)';
            for (weapon_owned of row.FindChildrenWithClassTraverse('weapon-selection-item-name-text-owned')) {
                weapon_owned.style.color = '#C9C9C9';
            }

            if (${showRarity})
            {
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-1")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#ffffff';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#ffffff 0px 0px 1px 1.75';
                    }
                }

                // Consumer Grade
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-1")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#B1C4D9';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#B1C4D9 0px 0px 1px 1.75';
                    }
                }

                // Industrial Grade
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-2")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#5F97DA';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#5F97DA 0px 0px 1px 1.75';
                    }
                }

                // Mil-Spec
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-3")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#4D69FF';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#4D69FF 0px 0px 1px 1.75';
                    }
                }

                // Restricted
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-4")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#8847FF';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#8847FF 0px 0px 1px 1.75';
                    }
                }

                // Classified
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-5")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#D32EE7';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#D32EE7 0px 0px 1px 1.75';
                    }
                }

                // Covert
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-6")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#EB4B4C';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#EB4B4C 0px 0px 1px 1.75';
                    }
                }
                // Knives
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item--rarity-7")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#EB4B4C';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#EB4B4C 0px 0px 1px 1.75';
                    }
                }

            }
        
        } else {
            row.style.backgroundImage = 'none';

            if (${showRarity})
            {
                for (rarity of row.FindChildrenWithClassTraverse("weapon-selection-item")) {
                    for (item of rarity.FindChildrenWithClassTraverse('weapon-selection-item-name-text')) {
                        item.style.color = '#ffffff';
                    }
                    for (icon of rarity.FindChildrenWithClassTraverse('weapon-selection-item-icon-main')) {
                        icon.style.imgShadow = '#00000000 0px 0px 0px 0';
                    }
                }
            }

        }
        row.style.marginBottom = '15px';
    }

    for (var row of hws.FindChildrenWithClassTraverse('weapon-row-number')) {
        row.style.fontSize = '16px';
        row.style.fontWeight = 'bold';
        row.style.transform = 'translateY(-5px)';
    }


}

$.Schedule(0.05, runner);
)weapsel"