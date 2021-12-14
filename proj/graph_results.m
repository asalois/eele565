clear; clc; close all;

%% inner loop
run_time= [34,97,121,143,174,177,192,183,194,193,202,205,203,202,198,202]
t=[1:15,20]


figure()
plot(t,run_time)
title("Run Time vs Threads for inner loop")
xlabel("Number Threads")
ylabel("Run Time (seconds)")

%% outer loop i9
run_time= [47,36,109,150,217,228,216,226,229,223,220,224,233,248]
t=[1:14]

%% 
figure()
plot(t,run_time)
title("Run Time vs Threads for outer loop on i9-10900F")
xlabel("Number Threads")
ylabel("Run Time (seconds)")


%% outer loop r5
run_time= [54,35,66,99,140,183,250,246,233,232,238,249,276,297]
t=[1:14]

%% 
figure()
plot(t,run_time)
title("Run Time vs Threads for outer loop on R5-4600U")
xlabel("Number Threads")
ylabel("Run Time (seconds)")