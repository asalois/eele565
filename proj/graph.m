clear; clc; close all;


run_time= [34,97,121,143,174,177,192,183,194,193,202,205,203,202,198,202]
t=[1:15,20]

%%
figure()
plot(t,run_time)
title("Run Time vs Threads at 4096")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
