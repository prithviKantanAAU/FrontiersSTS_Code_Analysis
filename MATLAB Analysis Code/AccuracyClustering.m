clc
close all
load 'Outcomes.mat'

clusterVector_ACC = kmeans(OUTCOME_accPerc_Subj_Blk,2);

cluster1_ACC = OUTCOME_accPerc_Subj_Blk(clusterVector_ACC == 1,:);
cluster2_ACC = OUTCOME_accPerc_Subj_Blk(clusterVector_ACC == 2,:);

figure
violinplot(cluster1_ACC);
figure
violinplot(cluster2_ACC);

% for i = 1 : length(OUTCOME_accPerc_Subj_Blk)
%     for j = 1 : 6
%         if clusterVector_ACC(i) == 1
%             plot(OUTCOME_accPerc_Subj_Blk(i,j),j);
%             hold on
%         end
%         
%         if clusterVector_ACC(i) == 2
%             plot(OUTCOME_accPerc_Subj_Blk(i,j),j);
%             hold on
%         end
%     end
% end