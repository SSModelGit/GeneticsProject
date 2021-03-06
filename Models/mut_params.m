%mut_params
mut.fertility = 0.000045; % 0.000035 is an amazing cyclic-looking breath taker
mut.M2Fprobability = 0.5;
mut.Y_C = 20;
mut.Y_R = 75;
mut.distribution=[4,11];
mut.distributionPercent=0.2;
mut.MSM = 0.0025; % Mortality Senior Male
mut.MSF = 0.0024; % Mortality Senior Female
% Senior death rate has no effect on population, as population dynamics is
% decoupled from the rest of the pop. They will not blow up given a
% non-zero death rate, as given no adults, they cannot grow.
yearInit=2000;
freqInit=interp1(dMat.year, dMat.PKU.freq, yearInit);
L_CMinit= 41245211;
L_CFinit= 39228054;
L_RMinit= 90702001;
L_RFinit=93645873;
L_SMinit= 6106351;
L_SFinit= 10494416;

% split01=0.5
% split01=56.5/95;
split01=65/96.5;
split01 = 0.9;

init.L_0CM_0 = [L_CMinit*(1-freqInit)*split01,0];
init.L_0CM_0(2) = init.L_0CM_0(1) * mut.Y_C * 0.5;

init.L_1CM_0 = [L_CMinit*(1-freqInit)*(1-split01),0];
init.L_1CM_0(2) = init.L_1CM_0(1) * mut.Y_C * 0.5;

init.L_2CM_0 = [L_CMinit*freqInit,0];
init.L_2CM_0(2) = init.L_2CM_0(1) * mut.Y_C * 0.5;

init.L_0CF_0 = [L_CFinit*(1-freqInit)*split01,0];
init.L_0CF_0(2) = init.L_0CF_0(1) * mut.Y_C * 0.5;

init.L_1CF_0 = [L_CFinit*(1-freqInit)*(1-split01),0];
init.L_1CF_0(2) = init.L_1CF_0(1) * mut.Y_C * 0.5;

init.L_2CF_0 = [L_CFinit*freqInit,0];
init.L_2CF_0(2) = init.L_2CF_0(1) * mut.Y_C * 0.5;

init.L_0RM_0 = [L_RMinit*(1-freqInit)*split01,0];
init.L_0RM_0(2) = init.L_0RM_0(1) * mut.Y_R * 0.5;

init.L_1RM_0 = [L_RMinit*(1-freqInit)*(1-split01),0];
init.L_1RM_0(2) = init.L_1RM_0(1) * mut.Y_R * 0.5;

init.L_2RM_0 = [L_RMinit*freqInit,0];
init.L_2RM_0(2) = init.L_2RM_0(1) * mut.Y_R * 0.5;

init.L_0RF_0 = [L_RFinit*(1-freqInit)*split01,0];
init.L_0RF_0(2) = init.L_0RF_0(1) * mut.Y_R * 0.5;

init.L_1RF_0 = [L_RFinit*(1-freqInit)*(1-split01),0];
init.L_1RF_0(2) = init.L_1RF_0(1) * mut.Y_R * 0.5;

init.L_2RF_0 = [L_RFinit*freqInit,0];
init.L_2RF_0(2) = init.L_2RF_0(1) * mut.Y_R * 0.5;

init.L_0SM_0 = [L_SMinit*(1-freqInit)*split01,0];
init.L_0SM_0(2) = init.L_0SM_0(1) * mut.Y_R * 1.1;

init.L_1SM_0 = [L_SMinit*(1-freqInit)*(1-split01),0];
init.L_1SM_0(2) = init.L_1SM_0(1) * mut.Y_R * 1.1;

init.L_2SM_0 = [L_SMinit*freqInit,0];
init.L_2SM_0(2) = init.L_2SM_0(1) * mut.Y_R * 1.1;


init.L_0SF_0 = [L_SFinit*(1-freqInit)*split01,0];
init.L_0SF_0(2) = init.L_0SF_0(1) * mut.Y_R * 1.1;

init.L_1SF_0 = [L_SFinit*(1-freqInit)*(1-split01),0];
init.L_1SF_0(2) = init.L_1SF_0(1) * mut.Y_R * 1.1;

init.L_2SF_0 = [L_SFinit*freqInit,0];
init.L_2SF_0(2) = init.L_2SF_0(1) * mut.Y_R * 1.1;

mut.mort=[0.00141, 0.00141, 0.042348, 0.042348, 0.21226, 0.21226];

mut.muMort = [0, 0, 0, 0, 0, 0; ...
              0, 0, 0, 0, 0, 0; ...
              0.25^(20), 0.20^(20), .85^(55), .75^(55), 1, 1];
          
          
popData = [ 299398484,	296507061,	293638158,	290796023,	288125973, ...
    285226284,	282216952,	281424602,	281421906];

popData = sort(popData);