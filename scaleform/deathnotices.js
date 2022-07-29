R"(
var contextPanel = $.GetContextPanel();

for (var dnBackground of contextPanel.FindChildrenWithClassTraverse('DeathNoticeBGBorder'))
{
	
	dnBackground.style.border = '0px solid #00000000';
	dnBackground.style.boxShadow = 'inset #00000000 0px 0px 0px 0px;';
	dnBackground.style.borderRadius = '0px';
}

for (var dnBackgroundg of contextPanel.FindChildrenWithClassTraverse('DeathNoticeBG'))
{
	dnBackgroundg.style.backgroundImage = 'url("https://images2.imgbox.com/49/45/mrwub2K0_o.png")';
    dnBackgroundg.style.backgroundSize = '100% 100%';
    dnBackgroundg.style.backgroundColor = '#00000000';
}

for (var dnIcon of contextPanel.FindChildrenWithClassTraverse('DeathNoticeIcon'))
{		
	if (dnIcon.id === "Weapon")
	{
		dnIcon.style.verticalAlign = 'top';
		dnIcon.style.transform = 'translateY(5px)';
		dnIcon.style.uiScale = "51%";
	} else
	{
    	 dnIcon.style.height = '20px';
		dnIcon.style.verticalAlign = 'top';
    	dnIcon.style.transform = 'translateY(0px) scaleY(.8) scaleX(.8)';
    	dnIcon.style.uiScale = "100%";
	}
}
    
for (var dnT of contextPanel.FindChildrenWithClassTraverse('DeathNoticeTColor'))
{
	dnT.style.color = '#e8c56f';
	
}
for (var dnCt of contextPanel.FindChildrenWithClassTraverse('DeathNoticeCTColor'))
{
	dnCt.style.color = '#83a5de';
	
}

for (var deathnotice of contextPanel.FindChildrenWithClassTraverse('DeathNotice'))
{
	// ---------------- ICON REMOVALS ----------------
	deathnotice.FindChildTraverse('NoScopeIcon').style.visibility = 'collapse';
	deathnotice.FindChildTraverse('ThroughSmokeIcon').style.visibility = 'collapse';
	deathnotice.FindChildTraverse('AttackerBlindIcon').style.visibility = 'collapse';
	deathnotice.FindChildTraverse('Domination').style.visibility = 'collapse';
	// ---------------- REMOVALS ----------------
	deathnotice.style.margin = '0px';
	if(deathnotice.BHasClass('DeathNotice_Killer'))
	{
		for (var killer of contextPanel.FindChildTraverse('HudDeathNotice').FindChildrenWithClassTraverse('DeathNotice_Killer'))
		{
			for(var content of killer.FindChildrenWithClassTraverse('DeathNoticeBG'))
            {
                content.style.border = '2px solid #8a121b';
				content.style.borderRadius = '3px';
                content.style.backgroundColor = '#000000ff';
                content.style.opacity = '0.9';
			}
		}
	}
	if(deathnotice.BHasClass('DeathNotice_Victim'))
	{
	    for (var victim of contextPanel.FindChildTraverse('HudDeathNotice').FindChildrenWithClassTraverse('DeathNotice_Victim'))
		{
		    for(var content of victim.FindChildrenWithClassTraverse('DeathNoticeBG'))
            {
            
                content.style.backgroundColor = '#0e0e0eB3';
		    	content.style.borderRadius = '3px';
                content.style.boxShadow = 'inset #e10000e6 0px 0px 1px;';
                content.style.opacity = '0.9';
		    }
	    }
    }
}
)"