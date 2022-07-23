R'(
    // ${style} - healthammo style
    var context_panel = $.GetContextPanel();
    context_panel.FindChildTraverse('HudHealthArmor').style.marginLeft = '0px';
    var hud_ha = context_panel.FindChildTraverse('HudHealthArmor');
    /* <---- REMOVALS ----> */
    hud_ha.FindChildTraverse('HudHealthBG').style.backgroundColor = '#00000000';
    hud_ha.FindChildTraverse('HudArmorBG').style.backgroundColor = '#00000000';
    /* <--------> */
    for(var hud_container of hud_ha.FindChildrenWithClassTraverse('hud-HA-icon-container'))
    {
        hud_container.style.x = '10px';
        hud_container.style.y = '3px';
        hud_container.style.width = '30px';
        hud_container.style.height = '100%';
        hud_container.style.opacity = '1.0';
        hud_container.style.marginTop = '-1px';
    }

    for(var hud_ha_armor of hud_ha.FindChildrenWithClassTraverse('hud-HA-armor1'))
    {
        hud_ha_armor.style.x = '38px';
        hud_ha_armor.style.y = '3px';
        hud_ha_armor.style.width = '70px';
        hud_ha_armor.style.fontSize = '42px';
        hud_ha_armor.style.fontWeight = 'bold';
        hud_ha_armor.style.color = '#ffffff';
        hud_ha_armor.style.letterSpacing = '0px';
        hud_ha_armor.style.horizontalAlign = 'left';
        hud_ha_armor.style.opacity = '0.95';
        hud_ha_armor.style.textShadow = '0px 0px 3px 0.0 #000000DD';
        hud_ha_armor.style.marginLeft = '5px';
        hud_ha_armor.style.textOverflow = 'shrink';
    }

    for(var hud_ha_health of hud_ha.FindChildrenWithClassTraverse('hud-HA-health1'))
    {
        hud_ha_health.style.x = '38px';
        hud_ha_health.style.y = '3px';
        hud_ha_health.style.width = '70px';
        hud_ha_health.style.fontSize = '42px';
        hud_ha_health.style.fontWeight = 'bold';
        hud_ha_health.style.color = '#ffffff';
        hud_ha_health.style.letterSpacing = '0px';
        hud_ha_health.style.horizontalAlign = 'center';
        hud_ha_health.style.opacity = '0.95';
        hud_ha_health.style.textShadow = '0px 0px 3px 0.0 #000000DD';
        hud_ha_health.style.marginLeft = '5px';
        hud_ha_health.style.textOverflow = 'shrink';
    }

    for(var hud_ha_text of hud_ha.FindChildrenWithClassTraverse('hud-HA-text'))
    {
        hud_ha_text.style.x = '42px';
        hud_ha_text.style.y = '4px';
    }

    for(var hud_ha_bar of hud_ha.FindChildrenWithClassTraverse('hud-HA-bar'))
    {
        hud_ha_bar.style.x = '108px';
        hud_ha_bar.style.y = '34px';
        hud_ha_bar.style.backgroundColor = '#03030399';
    }
    for(var hud_ha_generic of hud_ha.FindChildrenWithClassTraverse('hud-HA'))
    {
         hud_ha_generic.style.width = '465px';     
         hud_ha_generic.style.height = '55px';
	     hud_ha_generic.style.verticalAlign = 'bottom';
         hud_ha_generic.style.opacity = '0.0';
	     hud_ha_generic.style.transitionProperty = 'opacity';
	     hud_ha_generic.style.transitionTimingFunction = 'ease-in-out';
         hud_ha_generic.style.transitionDuration = '0.3s';
         hud_ha_generic.style.marginLeft = '0px';

         if(hud_ha_generic.BHasClass('hud-HA--active'))
         {
            for(var hud_ha_generic_active of hud_ha.FindChildrenWithClassTraverse('hud-HA--active'))
            {
                hud_ha_generic_active.style.opacity = '1.0';
            }
         } 
    }

    for(var survival of hud_ha.FindChildrenWithClassTraverse('survival'))
    {
        for(var inner of survival.FindChildrenWithClassTraverse('hud-HA'))
        {
            inner.style.width = '550px';
        }
    }

    for(var hud_ha_bg of hud_ha.FindChildrenWithClassTraverse('hud-HA-bg'))
    {
        hud_ha_bg.style.flowChildren = 'right';   
        hud_ha_bg.style.width = '100%';
        hud_ha_bg.style.height = '100%';
        hud_ha_bg.style.opacity = '1.0';
    }

    for(var hud_ha_bg_H of hud_ha.FindChildrenWithClassTraverse('hud-HA-bg-h'))
    {
        hud_ha_bg_H.style.backgroundImage = 'url("https://images2.imgbox.com/3b/5c/knQ8o3GI_o.png")'; // HP.png
        hud_ha_bg_H.style.backgroundSize = '107% 100%';
        hud_ha_bg_H.style.backgroundImgOpacity = '0.95';
        hud_ha_bg_H.style.width = '200px';
        hud_ha_bg_H.style.height = '100%';
        hud_ha_bg_H.style.horizontalAlign = 'left';
    }
       
    for(var hud_ha_bg_A of hud_ha.FindChildrenWithClassTraverse('hud-HA-bg-a'))
    {
        hud_ha_bg_A.style.backgroundImage = 'url("https://images2.imgbox.com/81/02/IrFgHYQq_o.png")'; // Armor.png
        hud_ha_bg_A.style.backgroundSize = '100% 100%';
        hud_ha_bg_A.style.backgroundImgOpacity = '1.0';
        hud_ha_bg_A.style.width = '100%';
        hud_ha_bg_A.style.height = ${isSimple} ? '120px' : '100%';
        hud_ha_bg_A.style.opacity = '0.95';
        hud_ha_bg_A.style.horizontalAlign = 'left';
        hud_ha_bg_A.style.overflow =  ${isSimple} ? 'noclip' + 'squish';
    }

    for(var ondmg of hud_ha.FindChildrenWithClassTraverse('hud-HA--on-damage'))
    {
        for(var dmg of ondmg.FindChildrenWithClassTraverse('hud-HA-text'))
        {
            dmg.style.washColor = '#ff0000';
        }
    }

    for(var oncrit of hud_ha.FindChildrenWithClassTraverse('hud-HA--critical'))
    {
      for(var hud_ha_bg of oncrit.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-bg-h'))
        {
            hud_ha_bg.style.backgroundImage = 'url("https://images2.imgbox.com/7b/d1/XeL3b9D9_o.png")';
            hud_ha_bg.style.backgroundImgOpacity = '0.92';
        }
    }

    for (var health of context_panel.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-icon--health'))
    {

        health.SetImage('https://images2.imgbox.com/3f/ad/nTYzLRen_o.png');
   		health.style.marginTop = '0px';
        health.style.overflow = 'noclip';
        health.style.backgroundColor = '#00000000';
    }

    for (var shield of context_panel.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-icon--armor'))
    {
        shield.SetImage('https://images2.imgbox.com/74/48/0CfxlpEt_o.png');
		shield.style.marginTop = '0px';
        shield.style.overflow = 'noclip';
        shield.style.backgroundColor = '#00000000';
    }

    for (var helmet  of context_panel.FindChildTraverse('HudHealthArmor').FindChildrenWithClassTraverse('hud-HA-icon--helmet'))
    {
        helmet.SetImage('https://images2.imgbox.com/74/48/0CfxlpEt_o.png');
		helmet.style.marginTop = '0px';
        helmet.style.overflow = 'noclip';
        helmet.style.backgroundColor = '#00000000';
    }
)'