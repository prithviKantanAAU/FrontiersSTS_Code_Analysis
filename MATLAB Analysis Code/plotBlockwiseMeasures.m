% ORDERED BY PRESENTATION BLOCK
OUTCOME_accPerc_Subj_Blk_ORDERED_Rel = OUTCOME_accPerc_Subj_Blk_ORDERED ./ OUTCOME_accPerc_Subj_MEAN'  .*100 - 100;
figure
%boxplot(OUTCOME_accPerc_Subj_Blk_ORDERED_Rel)
violinplot(OUTCOME_accPerc_Subj_Blk_ORDERED_Rel)
title('Normalized Accuracy Across Participants - Presentation Order')
xticklabels({'1st','2nd','3rd','4th','5th','6th'});
xlabel('Block Sequence Position')
ylabel('% of Participant Mean') 
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Block-Wise Outcomes\Accuracy - Presentation Order - Rel.fig'));

conPerc_Part_MEAN = mean(OUTCOME_conPerc_Subj_Blk,2);
OUTCOME_conPerc_Subj_Blk_Rel = OUTCOME_conPerc_Subj_Blk ./ conPerc_Part_MEAN .*100 - 100;
OUTCOME_conPerc_Subj_Blk_ORDERED_Rel = OUTCOME_conPerc_Subj_Blk_ORDERED ./ conPerc_Part_MEAN  .*100 - 100;

figure
%boxplot(OUTCOME_conPerc_Subj_Blk_Rel)
violinplot(OUTCOME_conPerc_Subj_Blk_Rel)
title('Normalized Confidence Across Participants')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
xlabel('Mapping Combination')
ylabel('% of Participant Mean')
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Block-Wise Outcomes\Confidence - Rel.fig'));

figure
%boxplot(OUTCOME_accPerc_Subj_Blk_ORDERED_Rel)
violinplot(OUTCOME_conPerc_Subj_Blk_ORDERED_Rel)
title('Normalized Confidence Across Participants - Presentation Order')
xticklabels({'1st','2nd','3rd','4th','5th','6th'});
xlabel('Block Sequence Position')
ylabel('% of Participant Mean')
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Block-Wise Outcomes\Confidence - Presentation Order - Rel.fig'));

rspTime_Part_MEAN = mean(OUTCOME_rspTime_Subj_Blk,2);
OUTCOME_rspTime_Subj_Blk_Rel = OUTCOME_rspTime_Subj_Blk ./ rspTime_Part_MEAN .*100 - 100;
OUTCOME_rspTime_Subj_Blk_ORDERED_Rel = OUTCOME_rspTime_Subj_Blk_ORDERED ./ rspTime_Part_MEAN .*100 - 100;

figure
%boxplot(OUTCOME_rspTime_Subj_Blk_Rel)
violinplot(OUTCOME_rspTime_Subj_Blk_Rel)
title('Normalized Response Time Across Participants')
xticklabels({'S','S+J','S+P','S+F+J','S+P+F','S+P+F+J'});
xlabel('Mapping Combination')
ylabel('% of Participant Mean') 
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Block-Wise Outcomes\Response Time - Rel.fig'));

figure
%boxplot(OUTCOME_accPerc_Subj_Blk_ORDERED_Rel)
violinplot(OUTCOME_rspTime_Subj_Blk_ORDERED_Rel)
title('Normalized Response Time Across Participants - Presentation Order')
xticklabels({'1st','2nd','3rd','4th','5th','6th'});
xlabel('Block Sequence Position')
ylabel('% of Participant Mean')
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Block-Wise Outcomes\Response Time - Presentation Order - Rel.fig'));