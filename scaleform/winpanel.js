R"(
var contextPanel = $.GetContextPanel();
var textColor = ${isCt} ? '#B4BBBE' : '#D6C8B5';
var winpanelBackground = ${isCt} ? 'https://images2.imgbox.com/9b/a5/igisaPg8_o.png' : ${isT} ? 'https://images2.imgbox.com/c9/be/43gnCOjE_o.png' : 'https://images2.imgbox.com9b/a5/igisaPg8_o.png';
if (${is2013})
    winpanelBackground = ${isCt} ? 'https://images2.imgbox.com/77/d5/T79ImP9g_o.png' : ${isT} ? 'https://images2.imgbox.com/26/56/eEUIVB7m_o.png' : 'https://images2.imgbox.com/77/d5/T79ImP9g_o.png';
for (var mvp of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP'))
{
    if (${pendingMvp})
    {
        mvp.style.visibility = 'visible';
        mvp.style.width = '815px';
    } else
    {
        mvp.style.visibility = 'collapse';
    }
}
for (var winPanelBg of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__MainBG')) {
    winPanelBg.style.marginTop = '-42px';
    winPanelBg.style.width = '815px';
    winPanelBg.style.height = '155px';
    winPanelBg.style.backgroundImage = `url(${winpanelBackground})`;
    winPanelBg.style.backgroundSize = 'cover';
    winPanelBg.style.marginLeft = '105px';
}
for (var teamTitle of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamFG__Title'))
{
   teamTitle.style.visibility = ${is2013} ? 'collapse' : 'visible';
   teamTitle.style.marginTop = '-45px';
   teamTitle.style.color = textColor;
   teamTitle.style.fontSize = '40px';
}
for (var star of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerStar')) {
    if (${pendingMvp})
    {
        star.style.visibility = ${is2013} ?'collapse' : 'visible';
        star.style.marginTop = "25%";
        star.style.marginLeft = "-2px";
        star.SetImage('https://cdn.discordapp.com/attachments/954389817536421908/957676079642980392/star.svg');
        star.style.transform = 'translateY(5px)';
    } else
    { 
        star.style.visibility = 'collapse';
    }
}
for (var playerName of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__WinnerName')){
    if (${pendingMvp})
    {
        playerName.style.visibility = 'visible';
        playerName.style.marginTop = ${is2013} ?"15px" : "20px";
        playerName.style.color = ${isCt} ?"#717377" : "#8A7E6C";
        playerName.style.marginLeft = ${is2013} ?"-4px" : "2px";
        playerName.style.fontSize = ${is2013} ?"22px" : "17px";
        playerName.style.fontWeight = ${is2013} ?'light' : 'bold';
        playerName.style.transform = 'translateY(5px)';
    } else
    { 
        playerName.style.visibility = 'collapse';
    }
}
for (var profileImg of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('MVP__Avatar'))
{
    if (${pendingMvp})
    {
        if (${is2013})
        {
            profileImg.style.visibility = 'visible';
            profileImg.style.zIndex = "500";
            profileImg.style.height = "59px";
            profileImg.style.width = "59px";
            profileImg.style.marginTop = "19px";
            profileImg.style.padding = '0px';
            profileImg.style.paddingTop = '2px';
            profileImg.style.backgroundSize = '50%';
            profileImg.style.marginLeft = "25px";
            profileImg.style.backgroundColor = 'gradient( linear, 0% 0%, 0% 100%, from( #7d7d7d ), to( #202020) )';
            for (var imgPadding of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('AvatarImage')) {
                imgPadding.style.padding = '0px';
            }
        } else
        {
            profileImg.style.visibility = 'visible';
            profileImg.style.zIndex = "1000";
            profileImg.style.height = "60px";
            profileImg.style.width = "60px";
            profileImg.style.backgroundColor = "#00000000";
            profileImg.style.marginTop = "19px";
            profileImg.style.paddingLeft = "0px";
            profileImg.style.marginLeft = "25px";
        }
    } else
    {
        profileImg.style.visibility = 'collapse';
    }
}
var funFact = contextPanel.FindChildTraverse('FunFactText');
if (!${is2013})
{
    funFact.style.width = '813px';
    funFact.style.x = '107px';
    funFact.style.marginTop = '5px';
    funFact.style.backgroundColor = '#000000CC';
}
else
{
    funFact.style.width = '813px';
    funFact.style.height = '40px';
    funFact.style.x = '107px';
    funFact.style.marginTop = '5px';
    funFact.style.backgroundColor = '#000000CC';
    funFact.style.textAlign = 'left';
    funFact.style.fontSize = '19px';
    funFact.style.fontWeight = 'light';
    funFact.style.verticalAlign = 'center';
    funFact.style.paddingTop = '10px';
    funFact.style.paddingLeft = '25px';
}
/* <--------- REMOVALS ---------->*/
for (var h of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__hrTop')) {h.style.x = '0';h.style.y = '0';h.style.width = '0';h.style.height = '0';}
for (var h of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__hrMid')) {h.style.x = '0';h.style.y = '0';h.style.width = '0';h.style.height = '0';}
for (var h of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__hrBot')) {h.style.x = '0';h.style.y = '0';h.style.width = '0';h.style.height = '0';}
for (var hideTeamIcon of contextPanel.FindChildTraverse('HudWinPanel').FindChildrenWithClassTraverse('TeamBG__DefaultLogo')){hideTeamIcon.style.visibility ='collapse'; hideTeamIcon.style.opacity = '0';}
)"