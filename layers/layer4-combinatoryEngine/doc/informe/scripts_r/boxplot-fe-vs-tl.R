# BOX_PLOT'S FOR VARIABLES
#It reads a matrix from a file and saves it into my_data.
my_data <- scan(file="result.txt", fill = TRUE, what=list(tl1=0, fe1=0, fe2=0, fe3=0, fe4=0, fe5=0, fe6=0, fe7=0, fe8=0, fe9=0))

#The output file features.
pdf(file="boxplot_fe_vs_therapyLenght.pdf", height=3.9, width=4)

#It generates the graphic.
box_plot <- boxplot(
                    list("1" = my_data$fe1, "2" = my_data$fe2, "3" = my_data$fe3, "4" = my_data$fe4, "5" = my_data$fe5, 
                         "6" = my_data$fe6, "7" = my_data$fe7, "8" = my_data$fe8, "9" = my_data$fe9),
                    lty = 1,  # line type
                    lwd = 0.65, # line width
                    lend = 1.8, # :|
                    border =('red'),
                    xlab = 'Therapy Length',
                    ylab = 'Free Energy',
                    xlim = c(0, 10),
                    font.lab = 9,
                    cex = 0.3,
                    cex.lab = 0.7,
                    cex.axis = 0.5,
                    cex.main = 0.9,
                    frame = FALSE,
                    main ='Five-Number Summary for \n Therapies Length', 
                    horizontal = FALSE
                   )
