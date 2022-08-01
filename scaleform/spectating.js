R"(
var contextPanel = $.GetContextPanel();
    
for(var spec_parent of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerParentContainer'))
{  
    spec_parent.style.height = '260px';
    spec_parent.style.width = '642px';
}
for(var spec_bg of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerBG'))
{  
   spec_bg.style.backgroundColor = '#0000004D';
   spec_bg.style.height = '100px';
   spec_bg.style.verticalAlign = 'top';
   spec_bg.style.overflow = 'noclip'
}

for(var spec_bgb of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerBG__Border'))
{  
    spec_bgb.style.backgroundColor = '#0000004D';
}

for(var spec_def_logo of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerBG__DefaultLogo'))
{  
    spec_def_logo.style.visibility = 'collapse';
}

for(var spec_top_strip of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerBG__TopStrip'))
{  
    spec_top_strip.style.visibility = 'collapse';
}

for(var spec_bottom_strip of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerBG__BottomStrip'))
{  
    spec_bottom_strip.style.backgroundColor = '#0000004D';
    spec_bottom_strip.style.height = '24px';
    spec_bottom_strip.style.transform = 'translateY(0px)';
}

for(var fix of contextPanel.FindChildrenWithClassTraverse('HudSpecplayer__ItemContainer'))
{
    fix.style.overflow = 'noclip'
}

for (var row of contextPanel.FindChildrenWithClassTraverse('weapon-row')) {
    if (row.BHasClass('weapon-row--selected')) {
        for(var x of row.FindChildrenWithClassTraverse('weapon-selection-item-name-text'))
        {
            for(var txt of contextPanel.FindChildrenWithClassTraverse('HudSpecplayer__ItemName'))
            {
                txt.text = x.text;
                txt.style.visibility = 'visible';
                txt.style.height = 'fit-children';
                txt.style.verticalAlign = 'bottom';
                txt.style.backgroundColor = '#00000000';
                txt.style.transform = 'translateY(13px) translateX(-5px)';
                txt.style.fontSize = '16px';
                txt.style.fontWeight = 'light'
            }
        }
    }
}

for(var spec_player_name of contextPanel.FindChildrenWithClassTraverse('HudSpecplayer__player-name'))
{  
    spec_player_name.style.verticalAlign = 'center';
    spec_player_name.style.transform = 'translateY(0px)'
    spec_player_name.style.fontSize = '36px';
    spec_player_name.style.fontWeight = 'bold';
    spec_player_name.style.fontFamily = 'Stratum2';
    spec_player_name.style.letterSpacing = '-1px';
    spec_player_name.style.textShadow = '0px 0px 0px 0.0 #000000';
}

for(var spec_root_avatar of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerRoot__avatar'))
{
    spec_root_avatar.style.height = '76px';
    spec_root_avatar.style.width = '76px';
    spec_root_avatar.style.marginTop = '-3px';
    spec_root_avatar.style.border = '0px solid #ff0000';
    spec_root_avatar.style.backgroundColor = 'gradient( linear, 0% 0%, 0% 100%, from( #838383 ), to( #303030 ) )';
    spec_root_avatar.style.padding = '3px'
}
for(var spec_k_hints of contextPanel.FindChildrenWithClassTraverse('HudSpecplayer__key-hints-text'))
{
    spec_k_hints.style.opacity = '1';
    spec_k_hints.style.verticalAlign = 'bottom';
    spec_k_hints.style.transform = 'translateY(63%) translateX(-10px)';
    spec_k_hints.style.fontSize = '17px';
    spec_k_hints.style.fontWeight = 'light';
    spec_k_hints.style.horizontalAlign = 'left';
    spec_k_hints.style.backgroundColor = '#00000000';
}
for(var spec_root_t of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerRoot--TeamT'))
{
    for(var names of spec_root_t.FindChildrenWithClassTraverse('HudSpecplayer__player-name'))
    {
        names.style.color = '#F7F4CB'
    }
}
for(var spec_root_ct of contextPanel.FindChildrenWithClassTraverse('HudSpecplayerRoot--TeamCT'))
{
    for(var names of spec_root_ct.FindChildrenWithClassTraverse('HudSpecplayer__player-name'))
    {
        names.style.color = '#E5F8FF'
    }
}
)"