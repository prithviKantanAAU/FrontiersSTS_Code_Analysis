figure
imagesc(OUTCOME_ConfMat_Precision_Blk_Pat')
colormap('jet')
colorbar
title('Precision')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
yticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Mapping Combination')
ylabel('Movement Pattern')
savefig(strcat(savePath,'Block-Wise Confusion Matrices\Precision.fig'));

figure
imagesc(OUTCOME_ConfMat_Recall_Blk_Pat')
colormap('jet')
colorbar
title('Recall')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
yticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Mapping Combination')
ylabel('Movement Pattern')
savefig(strcat(savePath,'Block-Wise Confusion Matrices\Recall.fig'));

figure
imagesc(OUTCOME_ConfMat_FMeasr_Blk_Pat')
colormap('jet')
colorbar
title('f-measure (Precision-Recall Harmonic Mean)')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
yticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Mapping Combination')
ylabel('Movement Pattern')
savefig(strcat(savePath,'Block-Wise Confusion Matrices\f-Measure.fig'));

blockwise_Responses_Matrix = blockwise_Responses_Matrix';
blockwise_ConfPerc_Matrix = blockwise_ConfPerc_Matrix';
blockwise_RespTime_Matrix = blockwise_RespTime_Matrix';