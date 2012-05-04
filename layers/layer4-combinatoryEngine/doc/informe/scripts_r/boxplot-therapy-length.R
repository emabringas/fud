# BOX_PLOT'S FOR VARIABLES
#It reads a matrix from a file and saves it into my_data.
my_data <- scan(file="result.txt", fill = TRUE, what=list(tl1=0, fe1=0, fe2=0, fe3=0, fe4=0, fe5=0, fe6=0, fe7=0, fe8=0, fe9=0))

#The output file features.
pdf(paper="special", file="boxplot_for_therapies_lenght.pdf", height=4.8, width=4)

#It generates the graphic.
box_plot <- boxplot(
                    list("1" = my_data$tl1),# "2" = my_data$fe2, "3" = my_data$fe3),
                    lty = 1,  # line type
                    lwd = 0.65, # line width
                    lend = 2.8, # :|
                    border =('red'),
                    xlab='Therapy Length',
                    xlim = c(0, 2),
                    font.lab = 1,
                    cex = 0.3,
                    cex.lab = 0.4,
                    cex.axis = 0.5,
                    cex.main = 0.9,
                    frame = FALSE,
                    line.main = 1,
                    main ='Five-Number Summary for \n Therapies Length', 
                    horizontal = TRUE
                   )
