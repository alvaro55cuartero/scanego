clear all;
close all;

X = importdata('values.csv');
G = importdata('classes.csv');

gplotmatrix(X, [], G);
figure;
silhouette(X,G);




%X1 = X(G==1,:);
%X2 = X(G==2,:);

%[Px, Py] = meshgrid(-8:0.4:14);
%P = [Px(:) Py(:)];

%C = 0.5 * cov(X1) + 0.5 * cov(X2);
%C = cov(X);

%Pd1 = pdist2(mean(X1), P);
%Pd2 = pdist2(mean(X2), P);

%Pd1 = pdist2(mean(X1), P, 'mahalanobis', C);
%Pd2 = pdist2(mean(X2), P, 'mahalanobis', C);


%Pg = 3 * ones(size(Pd1));
%Pg(Pd1 > Pd2) = 4;

%gplotmatrix([X; P], [], [G Pg], 'grgr', '**..');