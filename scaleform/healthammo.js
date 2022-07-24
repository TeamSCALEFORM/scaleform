R"(
    var contextPanel = $.GetContextPanel();
    contextPanel.FindChildTraverse('HudHealthArmor').style.marginLeft = '0px';
    var hudHa = contextPanel.FindChildTraverse('HudHealthArmor');
    /* <---- REMOVALS ----> */
    hudHa.FindChildTraverse('HudHealthBG').style.backgroundColor = '#00000000';
    hudHa.FindChildTraverse('HudArmorBG').style.backgroundColor = '#00000000';
    /* <--------> */
    for(var hud_container of hudHa.FindChildrenWithClassTraverse('hud-HA-icon-container'))
    {
        hud_container.style.x = '10px';
        hud_container.style.y = '3px';
        hud_container.style.width = '30px';
        hud_container.style.height = '100%';
        hud_container.style.opacity = '1.0';
        hud_container.style.marginTop = '-1px';
    }
    
    for(var hudHaArmor of hudHa.FindChildrenWithClassTraverse('hud-HA-armor1'))
    {
        hudHaArmor.style.x = '38px';
        hudHaArmor.style.y = '3px';
        hudHaArmor.style.width = '70px';
        hudHaArmor.style.fontSize = '42px';
        hudHaArmor.style.fontWeight = 'bold';
        hudHaArmor.style.color = '#ffffff';
        hudHaArmor.style.letterSpacing = '0px';
        hudHaArmor.style.horizontalAlign = 'left';
        hudHaArmor.style.opacity = '0.95';
        hudHaArmor.style.textShadow = '0px 0px 3px 0.0 #000000DD';
        hudHaArmor.style.marginLeft = '5px';
        hudHaArmor.style.textOverflow = 'shrink';
    }
    
    for(var hudHaHealth of hudHa.FindChildrenWithClassTraverse('hud-HA-health1'))
    {
        hudHaHealth.style.x = '38px';
        hudHaHealth.style.y = '3px';
        hudHaHealth.style.width = '70px';
        hudHaHealth.style.fontSize = '42px';
        hudHaHealth.style.fontWeight = 'bold';
        hudHaHealth.style.color = '#ffffff';
        hudHaHealth.style.letterSpacing = '0px';
        hudHaHealth.style.horizontalAlign = 'center';
        hudHaHealth.style.opacity = '0.95';
        hudHaHealth.style.textShadow = '0px 0px 3px 0.0 #000000DD';
        hudHaHealth.style.marginLeft = '5px';
        hudHaHealth.style.textOverflow = 'shrink';
    }
    
    for(var hudHaText of hudHa.FindChildrenWithClassTraverse('hud-HA-text'))
    {
        hudHaText.style.x = '42px';
        hudHaText.style.y = '4px';
    }
    
    for(var hudHaBar of hudHa.FindChildrenWithClassTraverse('hud-HA-bar'))
    {
        hudHaBar.style.x = '108px';
        hudHaBar.style.y = '34px';
        hudHaBar.style.backgroundColor = '#03030399';
    }
    for(var hudHaGeneric of hudHa.FindChildrenWithClassTraverse('hud-HA'))
    {
            hudHaGeneric.style.width = '465px';     
            hudHaGeneric.style.height = '55px';
            hudHaGeneric.style.verticalAlign = 'bottom';
            hudHaGeneric.style.opacity = '0.0';
            hudHaGeneric.style.transitionProperty = 'opacity';
            hudHaGeneric.style.transitionTimingFunction = 'ease-in-out';
            hudHaGeneric.style.transitionDuration = '0.3s';
            hudHaGeneric.style.marginLeft = '0px';
    
            if(hudHaGeneric.BHasClass('hud-HA--active'))
            {
            for(var hudHaGeneric_active of hudHa.FindChildrenWithClassTraverse('hud-HA--active'))
            {
                hudHaGeneric_active.style.opacity = '1.0';
            }
            } 
    }
    
    for(var survival of hudHa.FindChildrenWithClassTraverse('survival'))
    {
        for(var inner of survival.FindChildrenWithClassTraverse('hud-HA'))
        {
            inner.style.width = '550px';
        }
    }
    
    for(var hudHaBg of hudHa.FindChildrenWithClassTraverse('hud-HA-bg'))
    {
        hudHaBg.style.flowChildren = 'right';   
        hudHaBg.style.width = '100%';
        hudHaBg.style.height = '100%';
        hudHaBg.style.opacity = '1.0';
    }
    
    for(var hudHaBgH of hudHa.FindChildrenWithClassTraverse('hud-HA-bg-h'))
    {
        hudHaBgH.style.backgroundImage = 'url("https://images2.imgbox.com/3b/5c/knQ8o3GI_o.png")'; // HP.png
        hudHaBgH.style.backgroundSize = '107% 100%';
        hudHaBgH.style.backgroundImgOpacity = '0.95';
        hudHaBgH.style.width = '200px';
        hudHaBgH.style.height = '100%';
        hudHaBgH.style.horizontalAlign = 'left';
    }
        
    for(var hudHaBgA of hudHa.FindChildrenWithClassTraverse('hud-HA-bg-a'))
    {
        hudHaBgA.style.backgroundImage = 'url("https://images2.imgbox.com/81/02/IrFgHYQq_o.png")'; // Armor.png
        hudHaBgA.style.backgroundSize = '100% 100%';
        hudHaBgA.style.backgroundImgOpacity = '1.0';
        hudHaBgA.style.width = '100%';
        hudHaBgA.style.height = ${isShort} ? '120px' : '100%';
        hudHaBgA.style.opacity = '0.95';
        hudHaBgA.style.horizontalAlign = 'left';
        hudHaBgA.style.overflow =  ${isShort} ? 'noclip' : 'squish';
    }
    
    for(var onDmg of hudHa.FindChildrenWithClassTraverse('hud-HA--on-damage'))
    {
        for(var dmg of onDmg.FindChildrenWithClassTraverse('hud-HA-text'))
        {
            dmg.style.washColor = '#ff0000';
        }
    }
    
    for(var oncrit of hudHa.FindChildrenWithClassTraverse('hud-HA--critical'))
    {
        for(var hudHaBg of oncrit.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-bg-h'))
        {
            hudHaBg.style.backgroundImage = 'url("https://images2.imgbox.com/7b/d1/XeL3b9D9_o.png")';
            hudHaBg.style.backgroundImgOpacity = '0.92';
        }
    }
    
    for (var health of contextPanel.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-icon--health'))
    {
    
        health.SetImage('https://images2.imgbox.com/3f/ad/nTYzLRen_o.png');
        health.style.marginTop = '0px';
        health.style.overflow = 'noclip';
        health.style.backgroundColor = '#00000000';
    }
    
    for (var shield of contextPanel.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-icon--armor'))
    {
        shield.SetImage('https://images2.imgbox.com/74/48/0CfxlpEt_o.png');
        shield.style.marginTop = '0px';
        shield.style.overflow = 'noclip';
        shield.style.backgroundColor = '#00000000';
    }
    
    for (var helmet  of contextPanel.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-icon--helmet'))
    {
        helmet.SetImage('https://images2.imgbox.com/74/48/0CfxlpEt_o.png');
        helmet.style.marginTop = '0px';
        helmet.style.overflow = 'noclip';
        helmet.style.backgroundColor = '#00000000';
    }
    )"