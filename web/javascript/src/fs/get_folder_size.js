var fso = new ActiveXObject("Scripting.FileSystemObject");

var f = fso.GetFolder("c:\\windows");

var fc = new Enumerator(f.SubFolders);

for(; !fc.atEnd(); fc.moveNext())
{
    try{
        WScript.Echo( fc.item().Size + "\t\t" + fc.item().Name );
    }
    catch(e)
    {
        WScript.Echo("error:" + fc.item().Name + " " + e.name + " " + e.message)
    }
}
