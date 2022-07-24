R"(
var contextPanel = $.GetContextPanel();
var joinPanelCTBG = "https://cdn.discordapp.com/attachments/808866622701830186/977922886042026015/Group_69.png";
var joinPanelTBG = "https://cdn.discordapp.com/attachments/808866622701830186/977919617194418195/Group_66.png";
var joinPanelBotBG = "https://images2.imgbox.com/3c/af/3j6BFAy9_o.png";

for(var hudHint of contextPanel.FindChildrenWithClassTraverse('hud-hint'))
{
    hudHint.style.backgroundImage = "url('https://images2.imgbox.com/f1/60/1bTBT9qY_o.png')";
    hudHint.style.backgroundColor = '#00000000';
    hudHint.style.width = '450px';
    hudHint.style.height = '109px';
    hudHint.style.backgroundSize = '100% 100%';
    hudHint.style.overflow = 'noclip';
    hudHint.style.backgroundRepeat = 'no-repeat';
    hudHint.style.transform = 'translateY(-100px)';
    
}

for(var hudHintIcon of contextPanel.FindChildrenWithClassTraverse('hud-hint_icon'))
{
    hudHintIcon.style.visibility = 'collapse'; // removal
}
for(var hint of contextPanel.FindChildrenWithClassTraverse('hud-hint__icon'))
{
    hint.style.visibility = 'collapse'; // removal
}


for(var hudHintText of contextPanel.FindChildrenWithClassTraverse('hud-hint__text'))
{
    hudHintText.style.width = '75%';
    hudHintText.style.horizontalAlign = 'right';
    hudHintText.style.textAlign = 'left';
    hudHintText.style.height = '100%';
    hudHintText.style.verticalAlign = 'top';
    hudHintText.style.textOverflow = 'noclip';
    
}
for(var hudHintPriorityLabel of contextPanel.FindChildrenWithClassTraverse('hud-hint__priority-label'))
{
    hudHintPriorityLabel.style.horizontalAlign = 'left';
    hudHintPriorityLabel.style.x = '0px';
    hudHintPriorityLabel.style.width = '250px';
    hudHintPriorityLabel.style.overflow = 'noclip';
    hudHintPriorityLabel.style.fontSize = '20px';
    hudHintPriorityLabel.style.fontFamily = 'Stratum2';
    hudHintPriorityLabel.style.color = '#EA7861';
    hudHintPriorityLabel.style.opacity = '0.9';
    hudHintPriorityLabel.style.textAlign = 'left';
    hudHintPriorityLabel.style.textOverflow = 'noclip';
    hudHintPriorityLabel.style.letterSpacing = '0px';
    hudHintPriorityLabel.style.marginTop = '5px';

}
for(var hudHintLabel of contextPanel.FindChildrenWithClassTraverse('hud-hint__label'))
{
    hudHintLabel.style.horizontalAlign = 'left';
    hudHintLabel.style.height = '90px';
    hudHintLabel.style.verticalAlign = 'top';
    hudHintLabel.style.textOverflow = 'noclip';
    hudHintLabel.style.fontSize = '16px';
    hudHintLabel.style.opacity = '0.9'
}

var hudTeamCounter = contextPanel.FindChildTraverse('HudTeamCounter');
for (var hrTop of hudTeamCounter.FindChildrenWithClassTraverse('hrTop')) {
    hrTop.style.visibility = 'collapse'; // removal
}


var joinPanelCT = hudTeamCounter.FindChildTraverse('JoinPanelCT');
joinPanelCT.style.width = '630px';
joinPanelCT.style.height = '56px';
joinPanelCT.style.horizontalAlign = 'center';
joinPanelCT.style.flowChildren = 'none';
joinPanelCT.style.backgroundImage = `url(${joinPanelCTBG})`;
joinPanelCT.style.backgroundSize = '100% 100%';

var joinPanelT = hudTeamCounter.FindChildTraverse('JoinPanelT');
joinPanelT.style.width = '630px';
joinPanelT.style.height = '56px';
joinPanelT.style.horizontalAlign = 'center';
joinPanelT.style.flowChildren = 'none';
joinPanelT.style.backgroundImage = `url(${joinPanelTBG})`;
joinPanelT.style.backgroundSize = '100% 100%';

var joinPanelBot = hudTeamCounter.FindChildTraverse('JoinPanelBot');
joinPanelBot.style.width = '630px';
joinPanelBot.style.height = '56px';
joinPanelBot.style.horizontalAlign = 'center';
joinPanelBot.style.flowChildren = 'none';
joinPanelBot.style.backgroundImage = `url(${joinPanelBotBG})`;
joinPanelBot.style.backgroundSize = '100% 100%';

var entryTextCt = hudTeamCounter.FindChildTraverse('JoinTextCT');
entryTextCt.style.fontSize = '26px';
entryTextCt.style.fontWeight = 'black';
entryTextCt.style.horizontalAlign = 'center';
entryTextCt.style.verticalAlign = 'top';
entryTextCt.style.letterSpacing = '0px';
entryTextCt.style.marginTop = '12px';
entryTextCt.style.opacity = '0.85';	
entryTextCt.style.backgroundColor = 'none';
entryTextCt.style.backgroundImage = 'none';
entryTextCt.style.backgroundSize = '100% 100%';
entryTextCt.style.overflow = 'noclip';
entryTextCt.style.backgroundRepeat = 'no-repeat';
entryTextCt.style.backgroundPosition = '40px -5px';
entryTextCt.style.marginLeft = '0%';

var entryTextT = hudTeamCounter.FindChildTraverse('JoinTextT');
entryTextT.style.fontSize = '26px';
entryTextT.style.fontWeight = 'black';
entryTextT.style.horizontalAlign = 'center';
entryTextT.style.verticalAlign = 'top';
entryTextT.style.letterSpacing = '0px';
entryTextT.style.marginTop = '12px';
entryTextT.style.opacity = '0.85';	
entryTextT.style.backgroundColor = 'none';
entryTextT.style.backgroundImage = 'none';
entryTextT.style.backgroundSize = '100% 100%';
entryTextT.style.overflow = 'noclip';
entryTextT.style.backgroundRepeat = 'no-repeat';
entryTextT.style.backgroundPosition = '40px -5px';
var entryTextBot = hudTeamCounter.FindChildTraverse('JoinTextBot');
entryTextBot.style.fontSize = '26px';
entryTextBot.style.fontWeight = 'black';
entryTextBot.style.horizontalAlign = 'center';
entryTextBot.style.verticalAlign = 'top';
entryTextBot.style.letterSpacing = '0px';
entryTextBot.style.marginTop = '12px';
entryTextBot.style.opacity = '0.85';	
entryTextBot.style.backgroundColor = 'none';
entryTextBot.style.backgroundImage = 'none';
entryTextBot.style.backgroundSize = '100% 100%';
entryTextBot.style.overflow = 'noclip';
entryTextBot.style.backgroundRepeat = 'no-repeat';
entryTextBot.style.backgroundPosition = '40px -5px';
entryTextBot.style.marginLeft = '0%';
)"