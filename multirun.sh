#!/bin/bash

header="Arrival Rate, Service Time, Average Turnaround Time, Average Throughput, Average CPU Utilization, Average Ready Queue Length"
echo "$header" > "cmh_171_log.txt"

# Loop from 10 to 30 and run main.exe with arguments
for i in {10..30}; do
    ./hw4 $i 0.04 cmh_171_log.txt
done

