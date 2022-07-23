R"(
var deathNoticeBackgroundImg = "https://images2.imgbox.com/49/45/mrwub2K0_o.png"

var contextPanel = $.GetContextPanel();
for (var deathNotice of contextPanel.FindChildrenWithClassTraverse('DeathNotice'))
{
	// Icon removals
	deathNotice.FindChildTraverse('NoScopeIcon').style.visibility = 'collapse';
	deathNotice.FindChildTraverse('ThroughSmokeIcon').style.visibility = 'collapse';
    deathNotice.FindChildTraverse('AttackerBlindIcon').style.visibility = 'collapse';
    deathNotice.FindChildTraverse('Domination').style.visibility = 'collapse';

	deathNotice.style.margin = '0px';
	if (deathNotice.BHasClass('DeathNotice_Killer'))
	{
		for (var killer of contextPanel.FindChildTraverse('HudDeathNotice').FindChildrenWithClassTraverse('DeathNotice_Killer'))
		{
			for (var _ of killer.FindChildrenWithClassTraverse('DeathNoticeBGBorder'))
			{
				killer.style.border = '2px solid #8a121b';
            	killer.style.borderRadius = '3px';
                killer.style.backgroundColor = '#000000E6';
			}
			for (var content of killer.FindChildrenWithClassTraverse('DeathNoticeContent'))
            {
                content.style.transitionDelay = '5.0s';
            }
		}
	}
	
	if (deathNotice.BHasClass('DeathNotice_Victim'))
    {
    	for (var victim of contextPanel.FindChildTraverse('HudDeathNotice').FindChildrenWithClassTraverse('DeathNotice_Victim'))
        {
        	victim.style.backgroundColor = '#0e0e0e';
            victim.style.borderRadius = '3px';
            victim.style.boxShadow = 'inset #e10000e6 0px 0px 1px;';
    	}
	}
}

for (var deathNoticeBorder of contextPanel.FindChildrenWithClassTraverse('DeathNoticeBGBorder'))
{
       
	deathNoticeBorder.style.border = '0px solid #00000000';
	deathNoticeBorder.style.boxShadow = 'inset #00000000 0px 0px 0px 0px;';
	deathNoticeBorder.style.borderRadius = '0px';
}

for (var deathNoticeBackground of contextPanel.FindChildrenWithClassTraverse('DeathNoticeBG'))
{
	deathNoticeBackground.style.backgroundImage = `url(${deathNoticeBackgroundImg})`;
	deathNoticeBackground.style.backgroundSize = '100% 100%';
	deathNoticeBackground.style.backgroundColor = '#00000000';
}

for (var deathNoticeIcon of contextPanel.FindChildrenWithClassTraverse('DeathNoticeIcon'))
{
    deathNoticeIcon.style.height = '20px';                
	deathNoticeIcon.style.verticalAlign = 'top';
	deathNoticeIcon.style.transform = 'translateY(-1px) scaleY(.8) scaleX(.8)';
}

for (var deathNoticeT of contextPanel.FindChildrenWithClassTraverse('DeathNoticeTColor'))
{
	deathNoticeT.style.color = '#e8c56f';
}

for (var deathNoticeCT of contextPanel.FindChildrenWithClassTraverse('DeathNoticeCTColor'))
{
	deathNoticeCT.style.color = '#83a5de';
}
)"