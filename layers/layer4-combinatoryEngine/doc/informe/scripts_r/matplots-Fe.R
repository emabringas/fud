#The output file features.
pdf(file="matplotFe_new.pdf", height=4.3, width=5.5)

#It reads a matrix from a file and saves it into mat.
mat <- read.table ("matrix.txt", fill=TRUE)

mat <- mat [,-1] #It ereases the first column.
inv_mat <- t(mat)


#It generates the graphic.
matplot(inv_mat, # datos
        frame = TRUE, # dibuja el frame
        type = "l", # points with lines
        lty = 3,  # line type
        lwd = 0.5, # line width
        pch = 21:21, # style of points
        col = "gray5", # color vector
        cex = 0.1, # about the size of circles/points
        cex.axis = 0.5, # fontsize for axis
        main = "Free Energy per Therapies Length",
        cex.main = 0.9, 
        xlim = c(0.5, 9),
        ylim = c(-333, -303),
        xlab = "Therapy Length",
        ylab = "Free Energy",
        cex.lab = 0.5
        )
#it should be a for sentence
col1 <-c(mat[,1])
col2 <-c(mat[,2])
col3 <-c(mat[,3])
col4 <-c(mat[,4])
col5 <-c(mat[,5])
col6 <-c(mat[,6])
col7 <-c(mat[,7])
col8 <-c(mat[,8])
col9 <-c(mat[,9])
cols <- c (col1,col2,col3,col4,col5,col6,col7,col8,col9)

#it should be a for sentence
rows1 = rep (1,length (col1))
rows2 = rep (2,length (col2))
rows3 = rep (3,length (col3))
rows4 = rep (4,length (col4))
rows5 = rep (5,length (col5))
rows6 = rep (6,length (col6))
rows7 = rep (7,length (col7))
rows8 = rep (8,length (col8))
rows9 = rep (9,length (col9))
rows <- c(rows1,rows2,rows3,rows4,rows5,rows6,rows7,rows8,rows9)


lmm<-lm(cols~rows + I (rows^2))

#lmm<-lm(cols~rows + I (rows^2) + I (rows^3))

#lmm<-lm(cols~rows + I (rows^2)+ I (rows^3) + I (rows^4))

xx <- seq(min(rows),max(rows),len=200)
yy <- lmm$coef %*% rbind(1,xx,xx^2)

lines(xx,yy,lwd=2,col="red")

#shows a sumary.
summary (lmm)
coef(lmm)




