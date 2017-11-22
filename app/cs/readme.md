# powershell

  - excel
    ```
     Get-Process | Where Company | Export-Excel C:\Temp\ps.xlsx -Show  -IncludePivotTable -PivotRows Company -PivotData @Handles=”sum”} -IncludePivotChart -ChartType PieExploded3D
    ```

  - get folder size
    ```
    "{0:N2}" -f ((Get-ChildItem -path C:\InsertPathHere -recurse | Measure-Object -property length -sum ).sum /1MB) + " MB"

    #The initial 0 (the one that comes before the colon) represents the index number of the item to be formatted
    # The N represents the type of format to be applied; in this case, the N is short for Numeric.
    # The second 0 (the one after the N) is known as the “precision specifier,”
    ` ``