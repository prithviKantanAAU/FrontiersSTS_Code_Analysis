%% Repetition-wise Accuracy, Normalized Accuracy, Confidence, RespTime, Clusters

% figure
% %boxplot(OUTCOME_accPerc_Subj_MEAN_REPWISE)
% violinplot(OUTCOME_accPerc_Subj_MEAN_REPWISE)
% title('Repetition-wise Accuracy (%)')
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('Accuracy (%)')
% yline(16.6666,'-.r','Chance Level')
% savefig(strcat(savePath,'Repetition-Wise Accuracy\OVERALL - ABS.fig'));
% 
% figure
% %boxplot(OUTCOME_accPerc_Subj_MEAN_REPWISE_Rel)
% violinplot(OUTCOME_accPerc_Subj_MEAN_REPWISE_Rel)
% title('Normalized Repetition-wise Accuracy')
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('% of Participant Mean')
% yline(0,'-.r','Participant Mean')
% savefig(strcat(savePath,'Repetition-Wise Accuracy\OVERALL - Rel.fig'));
% 
% % Confidence - Repwise across sound files
% figure
% violinplot(OUTCOME_conPerc_SoundClip_REPWISE)
% title('Repetition-wise Confidence (%)')
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('Confidence (%)')
% savefig(strcat(savePath,'Sound File Repwise Confidence + Response\Confidence.fig'));
% 
% % Response Time - Repwise across sound files
% figure
% violinplot(OUTCOME_rspTime_SoundClip_REPWISE)
% title('Repetition-wise Response Time (sec)')
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('Response Time (sec)')
% savefig(strcat(savePath,'Sound File Repwise Confidence + Response\Response Time.fig'));

clusterVec_conPerc_repWise_SFiles = kmeans(OUTCOME_conPerc_SoundClip_REPWISE,2);
clusterVec_rspTime_repWise_SFiles = kmeans(OUTCOME_rspTime_SoundClip_REPWISE,2);

% figure
% subplot(1,2,1)
% violinplot(OUTCOME_rspTime_SoundClip_REPWISE(clusterVec_rspTime_repWise_SFiles == 1,:))
% title('Cluster 1')
% ylim([0 10])
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('Response Time (sec)')
% subplot(1,2,2)
% violinplot(OUTCOME_rspTime_SoundClip_REPWISE(clusterVec_rspTime_repWise_SFiles == 2,:))
% title('Cluster 2')
% ylim([0 10])
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('Response Time (sec)')
% sgtitle('Response Time Clusters (Sound Files)')
% savefig(strcat(savePath,'Sound File Repwise Confidence + Response\Response Time Clusters.fig'));
% 
% figure
% subplot(1,2,1)
% violinplot(OUTCOME_conPerc_SoundClip_REPWISE(clusterVec_conPerc_repWise_SFiles == 1,:))
% title('Cluster 1')
% ylim([0 100])
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('Confidence (%)')
% subplot(1,2,2)
% violinplot(OUTCOME_conPerc_SoundClip_REPWISE(clusterVec_conPerc_repWise_SFiles == 2,:))
% title('Cluster 2')
% ylim([0 100])
% xticklabels({'Rep 1','Rep 2','Rep 3'});
% xlabel('Repetition Number')
% ylabel('Confidence (%)')
% sgtitle('Confidence Clusters (Sound Files)')
% savefig(strcat(savePath,'Sound File Repwise Confidence + Response\Confidence Clusters.fig'));

clusterMat_rspTime = reshape(clusterVec_rspTime_repWise_SFiles,6,6);
clusterMat_conPerc = reshape(clusterVec_conPerc_repWise_SFiles,6,6);

figure
imagesc(clusterMat_rspTime)
%colorbar
cmap = jet(2);                                          % assigen colormap
colormap(cmap)
hold on
L = line(ones(2),ones(2), 'LineWidth',2);               % generate line 
set(L,{'color'},mat2cell(cmap,ones(1,2),3));            % set the colors according to cmap
legend('Fast','Slow')                                 % add as many legend entries as data
title('Response Time Clusters')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
yticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
hold on

xlabel('Mapping Combination')
ylabel('Movement Pattern')
savefig(strcat(savePath,'Sound File Repwise Confidence + Response\Response Time Clusters - By File.fig'));

figure 
imagesc(clusterMat_conPerc)
%colorbar
cmap = jet(2);                                          % assigen colormap
colormap(cmap)
hold on
L = line(ones(2),ones(2), 'LineWidth',2);               % generate line 
set(L,{'color'},mat2cell(cmap,ones(1,2),3));            % set the colors according to cmap
legend('High','Low')                                 % add as many legend entries as data
title('Confidence Clusters')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
yticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Mapping Combination')
ylabel('Movement Pattern')
savefig(strcat(savePath,'Sound File Repwise Confidence + Response\Confidence Clusters - By File.fig'));
