if (Test-Path "log.txt") {
    Remove-Item "log.txt"
    }

$header = "Arrival Rate, Service Time, Average Turnaround Time, Average Throughput, Average CPU Utilization, Average Ready Queue Length"
Set-Content "results.txt" $header

for ($i = 10; $i -le 30; $i++)
{
    & .\main.exe $i 0.04
    }