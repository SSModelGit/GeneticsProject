%plotR
res.screenEff = [0,0.25,0.5,0.75,1];
res.deltaPop  = [100,200,300,400,500];
res.FinalAlleleRecessive = [0.1,0.2,0.3,0.4,0.5];

scatter(res.screenEff,res.deltaPop,(res.FinalAlleleRecessive).^4*10000,'filled')
figure
subplot(2,1,1)
plot(res.screenEff, res.deltaPop)
subplot(2,1,2)
plot(res.screenEff, res.FinalAlleleRecessive)