R"(
var hudTeamCounter = $.GetContextPanel().FindChildTraverse('HudTeamCounter');

if(${isCompetetive})
{
    for(var avatarBackground of hudTeamCounter.FindChildrenWithClassTraverse('AvatarL__Default--CT'))
    {
        avatarBackground.style.backgroundSize = '92% 86%';
        avatarBackground.style.backgroundPosition = '50% 25%';
        avatarBackground.style.backgroundRepeat = 'no-repeat';
    }
    for(var avatarBackground of hudTeamCounter.FindChildrenWithClassTraverse('AvatarL__Default--T'))
    {
        avatarBackground.style.backgroundSize = '92% 86%';
        avatarBackground.style.backgroundPosition = '50% 25%';
        avatarBackground.style.backgroundRepeat = 'no-repeat';
        
    }
    for(var avatarClr of hudTeamCounter.FindChildrenWithClassTraverse('AvatarL__PlayerColor'))
    {
        avatarClr.style.y = '-2px';
        avatarClr.style.width = '24px';
        avatarClr.style.height = '12px';
        avatarClr.style.marginLeft = '6px';
        avatarClr.style.horizontalAlign = 'center';
        avatarClr.style.imgShadow = '0px 0px 1px 1.0 #000000CC';
    }
    for(avatarL of hudTeamCounter.FindChildrenWithClassTraverse('AvatarL__Internal'))
    {
        avatarL.style.height = '59px';
        avatarL.style.width = '85%';
        avatarL.style.horizontalAlign = 'center';
        avatarL.style.verticalAlign = 'top';
        avatarL.style.backgroundColor = '#7f7f7f';
    }

    for(var avatarL of hudTeamCounter.FindChildrenWithClassTraverse('AvatarL_HealthBarBG'))
    {
        avatarL.style.verticalAlign = 'bottom';
        avatarL.style.marginBottom = '1.5px';
        avatarL.style.marginRight = '1.5px';
        avatarL.style.marginLeft = '1.5px';
        avatarL.style.height = '4.55px';
        avatarL.style.backgroundColor = '#00000040';
        avatarL.style.position = 'absolute';
    }

    for(var avbg of hudTeamCounter.FindChildrenWithClassTraverse('AvatarL__ImageBG'))
    {
        avbg.style.width = '85%';
        avbg.style.height = '59px';
    }

    for(var avatarL of hudTeamCounter.FindChildrenWithClassTraverse('AvatarL'))
    {
        avatarL.style.width = '58px';
        avatarL.style.height = '100px';
        avatarL.style.overflow = 'noclip';
    }
}
else{
    for (var avatarS of hudTeamCounter.FindChildrenWithClassTraverse('AvatarS'))
    {
        avatarS.style.width = '40px';
        avatarS.style.height = '22px';
    }

    for(var avatarS of hudTeamCounter.FindChildrenWithClassTraverse('AvatarS__Internal'))
    {
        avatarS.style.opacity = '1';
        avatarS.style.width = '25px';
        avatarS.style.height = '28.6px';
        avatarS.style.backgroundColor = '#7f7f7f'; 
        avatarS.style.verticalAlign = 'top';
    }

    for(var avatarS of hudTeamCounter.FindChildrenWithClassTraverse('AvatarS__PlayerImage'))
    {
        avatarS.style.backgroundColor = 'black';
        avatarS.style.width = '100%';
        avatarS.style.height = '100%';
        avatarS.style.verticalAlign = 'middle';
    }
        

    for(var avatarS of hudTeamCounter.FindChildrenWithClassTraverse('AvatarS__HealthBar')){
        avatarS.style.height = '3px';
        avatarS.style.verticalAlign = 'bottom';
    }

    for(var avatarS of hudTeamCounter.FindChildrenWithClassTraverse('AvatarS__Default--CT'))
    {
        avatarS.style.backgroundSize = '100% 180%';
        avatarS.style.backgroundPosition = 'center';
        avatarS.style.height = '100%'
    }

    for(var avatarS of hudTeamCounter.FindChildrenWithClassTraverse('AvatarS__Default--T'))
    {
        avatarS.style.backgroundSize = '100% 180%';
        avatarS.style.backgroundPosition = 'center';
        avatarS.style.height = '100%';
    }
}


for(var internalColor of hudTeamCounter.FindChildrenWithClassTraverse('AvatarImageT__Color'))
{
    internalColor.style.backgroundColor = '#87663e';
    internalColor.style.border = '2px solid #8a6a41';
}

for(var internalColor of hudTeamCounter.FindChildrenWithClassTraverse('AvatarImageT__InternalColor'))
{
    internalColor.style.backgroundColor = '#FFFFFF';
}


for(var internalColor of hudTeamCounter.FindChildrenWithClassTraverse('AvatarImageCT__Color'))
{
    internalColor.style.backgroundColor = '#72859d';
    internalColor.style.border = '2px solid #72859d';
}

for(var internalColor of hudTeamCounter.FindChildrenWithClassTraverse('AvatarImageCT__InternalColor'))
{
    internalColor.style.backgroundColor = '#FFFFFF';
}

for(var noOutline of hudTeamCounter.FindChildrenWithClassTraverse('Avatar__PlayerOutline--None'))
{
    noOutline.style.border = '0px solid #0000000';
}

for(var avatarOutline of hudTeamCounter.FindChildrenWithClassTraverse('Avatar__PlayerOutline--White'))
{
    avatarOutline.style.border = '4px solid white';
}


for (var avatarOutline of hudTeamCounter.FindChildrenWithClassTraverse('Avatar__PlayerOutline--T'))
{
    avatarOutline.style.backgroundColor = '#756337';
    avatarOutline.style.border = '2px solid #87663e';
}

for (var avatarOutline of hudTeamCounter.FindChildrenWithClassTraverse('Avatar__PlayerOutline--CT'))
{
    avatarOutline.style.backgroundColor = '#7C858F';
    avatarOutline.style.border = '2px solid #4F5D6D';
}

for (var av of hudTeamCounter.FindChildrenWithClassTraverse('Avatar__HealthBar--Normal'))
{
    av.style.backgroundColor = '#99ae91';
}

)"