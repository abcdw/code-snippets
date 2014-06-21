$dir = ".\*"
$tr_map = @{"�"="a"; "�"="b"; "�"="v"; "�"="g"; "�"="d"; "�"="e"; "�"="yo"; "�"="zh"; "�"="z"; "�"="i"; "�"="j"; "�"="k"; "�"="l"; "�"="m"; "�"="n"; "�"="o"; "�"="p"; "�"="r"; "�"="s"; "�"="t"; "�"="u"; "�"="f"; "�"="x"; "�"="c"; "�"="ch"; "�"="sh"; "�"="w"; "�"="#"; "�"="'"; "�"="y"; "�"="je"; "�"="yu"; "�"="ya"}
#
$current_date = Get-Date # -format yyyyMM
$current_date = Get-Date $current_date.AddMonths(-1) -format yyyyMM

Get-ChildItem $dir -Include *.* | ForEach-Object {
	$old_name = (Select-String -Pattern "[�-�]" -InputObject $_.FullName).Line
	if (![System.String]::IsNullOrEmpty($old_name)){
		$f_name = [System.IO.Path]::GetFileNameWithoutExtension(($old_name -replace "\s","_"))
		$f_exst = [System.IO.Path]::GetExtension(($old_name -replace "\s","_"))
		$new_name = ""
		foreach($c in $f_name.ToCharArray()) {
			if ($tr_map.ContainsKey($c.ToString())) {
				$new_name += $tr_map[$c.ToString()]
			} else {
				$new_name += $c
			}
		}
        $new_name = $new_name.Substring(0,1).ToUpper() + $new_name.Substring(1).ToLower()
		$new_name += $current_date + $f_exst
		Write-Host ($old_name + " --> " + $new_name)
		Rename-Item -Path $old_name -NewName $new_name
	}
}