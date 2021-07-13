clear all;
close all;
clc;

A = dlmread('Valores_Teoricos.txt');
x = A(:, 1);
y = A(:, 2);

A = dlmread('Valores_Poter.txt');
z = A(:, 1);
k = A(:, 2);

plot (x, y, z, k, '-', 'linewidth', 1)
set(gca,'fontsize', 10,'linewidth',1)
