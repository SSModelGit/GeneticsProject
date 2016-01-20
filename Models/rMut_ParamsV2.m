%mut_params
mut.fertility = 0.01265;
mut.M2Fprobability = 0.5;
mut.Y_C = 16;
mut.Y_R = 50;
mut.distribution=3;
mut.distributionPercent=0.1;
mut.MSM = 0.025; % Mortality Senior Male
mut.MSF = 0.4; % Mortality Senior Female
% Senior death rate has no effect on population, as population dynamics is
% decoupled from the rest of the pop. They will not blow up given a
% non-zero death rate, as given no adults, they cannot grow.

init.L_0CM_0 = [66,66*14];
init.L_1CM_0 = [66,66*14];
init.L_2CM_0 = [68,68*14];
init.L_0CF_0 = [66,66*14];
init.L_1CF_0 = [66,66*14];
init.L_2CF_0 = [68,68*14];
init.L_0RM_0 = [33,33*25];
init.L_1RM_0 = [33,33*25];
init.L_2RM_0 = [34,34*25];
init.L_0RF_0 = [33,33*25];
init.L_1RF_0 = [33,33*25];
init.L_2RF_0 = [34,34*25];
init.L_0SM_0 = [17,17*75];
init.L_1SM_0 = [17,17*75];
init.L_2SM_0 = [16,16*75];
init.L_0SF_0 = [17,17*75];
init.L_1SF_0 = [17,17*75];
init.L_2SF_0 = [16,16*75];

