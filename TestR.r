# Load necessary libraries
library(dplyr)
library(ggplot2)
library(lubridate)

data <- read.csv("~/Downloads/data.csv")

# Convert the Date column to Date format
data$Date <- as.Date(data$Date)

# Create a scatter plot of Diversity vs Date, colored by Ice category
scatter_plot <- ggplot(data, aes(x = Date, y = Diversity, color = Ice)) +
  geom_point(alpha = 0.7) +  # Add points
  geom_smooth(method = "lm", se = FALSE) +  # Add a linear trend line
  labs(title = "Scatter Plot of Diversity Over Time by Ice Category",
       x = "Date",
       y = "Diversity") +
  theme_minimal()

ggsave("~/Downloads/diversity_scatter_plot.png", plot = scatter_plot, width = 8, height = 6)
