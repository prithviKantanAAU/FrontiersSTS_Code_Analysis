% Plot Blockwise Outcomes

% Confidence
figure
%boxplot(OUTCOME_conPerc_Subj_Blk);
violinplot(OUTCOME_conPerc_Subj_Blk);
title('Mean Confidence (%) Across Participants')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
xlabel('Mapping Combination')
ylabel('Confidence (%)')
savefig(strcat(savePath,'Block-Wise Outcomes\Confidence - Abs.fig'));

% Accuracy
figure
%boxplot(OUTCOME_accPerc_Subj_Blk)
violinplot(OUTCOME_accPerc_Subj_Blk)
title('Accuracy (%) Across Participants')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
xlabel('Mapping Combination')
ylabel('Accuracy (%)')
yline(16.6666,'-.r','Chance Level')
savefig(strcat(savePath,'Block-Wise Outcomes\Accuracy - Abs.fig'));


OUTCOME_accPerc_Subj_Blk_Rel = OUTCOME_accPerc_Subj_Blk ./ OUTCOME_accPerc_Subj_MEAN' .*100 - 100;
figure
%boxplot(OUTCOME_accPerc_Subj_Blk_Rel)
violinplot(OUTCOME_accPerc_Subj_Blk_Rel)
title('Normalized Accuracy Across Participants')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
xlabel('Mapping Combination')
ylabel('% of Participant Mean') 
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Block-Wise Outcomes\Accuracy - Rel.fig'));

% Accuracy - Order
figure
%boxplot(OUTCOME_accPerc_Subj_Blk_ORDERED)
violinplot(OUTCOME_accPerc_Subj_Blk_ORDERED)
title('Accuracy (%) Across Participants - Presentation Order')
xticklabels({'1st','2nd','3rd','4th','5th','6th'});
xlabel('Block Sequence Position')
ylabel('Accuracy (%)')
yline(16.6666,'-.r','Chance Level')
savefig(strcat(savePath,'Block-Wise Outcomes\Accuracy - Presentation Order - Abs.fig'));

% Accuracy - MSoph Group
figure
for i = 1 : 2
    subplot(1,2,i)
    violinplot(OUTCOME_accPerc_Subj_Blk(MSoph_Grp == i,:))
    title(sprintf('Musical Sophistication Group %d',i));
    ylim([0 100])
    xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
    xlabel('Mapping Combination')
    ylabel('Accuracy (%)')
    yline(16.6666,'-.r','Chance Level')
end
sgtitle('Accuracy (%) Across Sophistication Groups')
savefig(strcat(savePath,'Block-Wise Outcomes\Accuracy - Abs - MSoph.fig'));

% Confidence - MSoph Group
figure
for i = 1 : 2
    subplot(1,2,i)
    violinplot(OUTCOME_conPerc_Subj_Blk(MSoph_Grp == i,:))
    title(sprintf('Musical Sophistication Group %d',i));
    ylim([0 100])
    xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
    xlabel('Mapping Combination')
    ylabel('Confidence (%)')
end
sgtitle('Confidence (%) Across Sophistication Groups')
savefig(strcat(savePath,'Block-Wise Outcomes\Confidence - Abs - MSoph.fig'));

% Confidence - Order
figure
%boxplot(OUTCOME_accPerc_Subj_Blk_ORDERED)
violinplot(OUTCOME_conPerc_Subj_Blk_ORDERED)
title('Confidence (%) Across Participants - Presentation Order')
xticklabels({'1st','2nd','3rd','4th','5th','6th'});
xlabel('Block Sequence Position')
ylabel('Confidence (%)')
savefig(strcat(savePath,'Block-Wise Outcomes\Confidence - Presentation Order - Abs.fig'));

% Response Time
figure
%boxplot(OUTCOME_rspTime_Subj_Blk)
violinplot(OUTCOME_rspTime_Subj_Blk)
title('Mean Response Time (sec) Across Participants')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
xlabel('Mapping Combination')
ylabel('Response Time (sec)')
savefig(strcat(savePath,'Block-Wise Outcomes\Response Time - Abs.fig'));

% Response TIme - MSoph Group
figure
for i = 1 : 2
    subplot(1,2,i)
    violinplot(OUTCOME_rspTime_Subj_Blk(MSoph_Grp == i,:))
    title(sprintf('Musical Sophistication Group %d',i));
    ylim([0 20])
    xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
    xlabel('Mapping Combination')
    ylabel('Response Time (sec)')
end
sgtitle('Response Time (sec) Across Sophistication Groups')
savefig(strcat(savePath,'Block-Wise Outcomes\Response Time - Abs - MSoph.fig'));

% Response Time - Order
figure
%boxplot(OUTCOME_accPerc_Subj_Blk_ORDERED)
violinplot(OUTCOME_rspTime_Subj_Blk_ORDERED)
title('Response Time (sec) Across Participants - Presentation Order')
xticklabels({'1st','2nd','3rd','4th','5th','6th'});
xlabel('Block Sequence Position')
ylabel('Response Time (sec)')
savefig(strcat(savePath,'Block-Wise Outcomes\Response Time - Presentation Order - Abs.fig'));