clear; clc; close all;

% %% inner loop
% run_time= [34,97,121,143,174,177,192,183,194,193,202,205,203,202,198,202];
% t=[1:15,20];
%
% figure()
% plot(t,run_time,"-*")
% title("Run Time vs Threads for inner loop")
% xlabel("Number Threads")
% ylabel("Run Time (seconds)")


%% outer loop i9
run_time= [47,36,109,150,217,228,216,226,229,223,220,224,233,248];
t= 1:14;
scale_i9_single = run_time/run_time(1);


figure()
plot(t,run_time,"-*")
title("Run Time for outer loop on i9-10900F @ 2^{14}")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
saveas(gcf,"single_i9.png")

%% outer loop i9
t = 1:14;
tvt = readmatrix('i9.csv');
tvt = sortrows(tvt);
times = reshape(tvt(:,2),3,14);
%times = [run_time; times];
md_i9 = mean(times);
scale_i9 = md_i9/md_i9(1);

% box plot with 50 per thread count
% figure()
% boxplot(times)
% title("Run Time for outer loop on Hyalite @ 2^{12}")
% xlabel("Number Threads")
% ylabel("Run Time (seconds)")


figure()
plot(t,md_i9,"-*")
title("Run Time for outer loop on i9-10900F @ 2^{14}")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
saveas(gcf,"i9.png")
%% r5
tvt = readmatrix('r5.csv');
tvt = sortrows(tvt);
times = reshape(tvt(:,2),6,14);
md_r5 = mean(times);
scale_r5 = md_r5/md_r5(1);


figure()
plot(t,md_r5,"-*")
title("Run Time for outer loop on r5-4600U @ 2^{14}")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
saveas(gcf,"r5.png")


%% Hyalite 2^16
tvt = readmatrix('outer_times_hyalite_16.csv');
times = reshape(tvt(:,2),50,14);
md_16 = median(times);
scale_16 = md_16/md_16(1);

%
figure()
plot(t,md_16,"-*")
title("Run Time for outer loop on Hyalite @ 2^{16}")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
saveas(gcf,"hyalite_16.png")

%% Hyalite 2^14
tvt = readmatrix('outer_times_hyalite_14.csv');
times = reshape(tvt(:,2),40,14);
md_14 = median(times);
scale_14 = md_14/md_14(1);

% box plot with 40
% figure()
% boxplot(times)
% title("Run Time for outer loop on Hyalite @ 2^{14}")
% xlabel("Number Threads")
% ylabel("Run Time (seconds)")

%
figure()
plot(t,md_14,"-*")
title("Run Time for outer loop on Hyalite @ 2^{14}")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
saveas(gcf,"hyalite_14.png")

%% Hyalite 2^12
tvt = readmatrix('outer_times_hyalite_12.csv');
times = reshape(tvt(:,2),50,14);
md_12 = median(times);
scale_12 = md_12/md_12(1);

% box plot with 50 per thread count
% figure()
% boxplot(times)
% title("Run Time for outer loop on Hyalite @ 2^{12}")
% xlabel("Number Threads")
% ylabel("Run Time (seconds)")

%
figure()
plot(t,md_12,"-*")
title("Run Time for outer loop on Hyalite @ 2^{12}")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
saveas(gcf,"hyalite_12.png")

%% Hyalite 2^12
tvt = readmatrix('mpi.csv');
times = reshape(tvt(:,2),50,13);
md_mpi = median(times);
scale_mpi = md_mpi/md_mpi(1);

% box plot with 50 per thread count
% figure()
% boxplot(times)
% title("Run Time for outer loop on Hyalite @ 2^{12}")
% xlabel("Number Threads")
% ylabel("Run Time (seconds)")

%
figure()
plot(2:14,md_mpi,"-*")
title("Run Time for mpi on Hyalite @ 2^{14}")
xlabel("Number Threads")
ylabel("Run Time (seconds)")
saveas(gcf,"hyalite_mpi_14.png")

%% scale hyalite
figure()
plot(t,scale_12,"-*",t,scale_14,"-*",t,scale_16,"-*",2:14,scale_mpi,"-*")
title("Slow Down on Hyalite")
xlabel("Number Threads")
ylabel("time/single thread time")
legend("Hyalite 2^{12}","Hyalite 2^{14}","Hyalite 2^{16}","Hyalite MPI 2^{14}",'Location','southeast')
saveas(gcf,"hyalite_scale.png")

%% scale all 2^14
figure()
plot(t,scale_14,"-*",t,scale_r5,"-*",t,scale_i9,"-*")
title("Slow Down at 2^{14}")
xlabel("Number Threads")
ylabel("time/single thread time")
legend("Hyalite","4600U","10900F",'Location','southeast')
saveas(gcf,"scale_14.png")


