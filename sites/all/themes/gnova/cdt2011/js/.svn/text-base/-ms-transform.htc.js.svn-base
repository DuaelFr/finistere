//oObj input requires that a matrix filter be applied.
//deg input defines the requested angle of rotation.
var deg2radians = Math.PI * 2 / 360;
function fnSetRotation(oObj, deg)
{   rad = deg * deg2radians ;
    costheta = Math.cos(rad);
	sintheta = Math.sin(rad);
 
    oObj.filters.item(0).M11 = costheta;
	oObj.filters.item(0).M12 = -sintheta;
    oObj.filters.item(0).M21 = sintheta;
    oObj.filters.item(0).M22 = costheta;
 
}