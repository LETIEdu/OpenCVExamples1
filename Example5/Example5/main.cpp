#include <iostream>
#include <opencv2/opencv.hpp>

/*
 * Поиск горизонтальных линий на изображении с помощью
 * морфологических операторов
 *
 */

int main()
{
    cv::Mat src = cv::imread("../../img/notes.png");
    // Проверяем загрузилось ли изображение
    if(!src.data)
    {
        std::cerr << "Problem loading image!!!" << std::endl;
        return -1;
    }
    cv::imshow("src", src);
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::Mat bw;
    // Используем адаптивную пороговую функцию
    //для получения бинарного изображения
    // (~) - побитовая инверсия
    cv::adaptiveThreshold(~gray,                      // Исходное изображение
                          bw,                         // Результат
                          255,                        // Максимальное значение
                          CV_ADAPTIVE_THRESH_MEAN_C,  // Адаптивный метод
                          cv::THRESH_BINARY,          // Режим порога
                          15,                         // Размер окна
                          0);                         // Вычитаемая константа
    cv::Mat horizontal = bw.clone();
    cv::Mat vertical = bw.clone();
    // Задаём размер окна для морфологических операторов
    int horizontalsize = horizontal.cols / 10;
    // Создаём форму сканирующего окна для морфологических операторов
    // в виде горизонтальной линии высотой 1 пиксель
    cv::Mat horizontalStructure = cv::getStructuringElement(
                cv::MORPH_RECT,              // Форма окна - прямоугольник
                cv::Size(horizontalsize, 1)  // Размер
                );
    // Применяем морфологические операторы
    cv::erode(horizontal,           // Исходное изображение
              horizontal,           // Результат
              horizontalStructure,  // Форма сканирующего окна
              cv::Point(-1, -1)     // Якорь (центральная точка)
              );
    cv::dilate(horizontal,          // Исходное изображение
               horizontal,          // Результат
               horizontalStructure, // Форма сканирующего окна
               cv::Point(-1, -1)    // Якорь (центральная точка)
               );
    cv::imshow("horizontal", ~horizontal);
    int verticalsize = vertical.rows / 30;
    cv::Mat verticalStructure = cv::getStructuringElement(cv::MORPH_RECT,
                                    cv::Size(1, verticalsize));
    cv::erode(vertical, vertical, verticalStructure, cv::Point(-1, -1));
    cv::dilate(vertical, vertical, verticalStructure, cv::Point(-1, -1));
    cv::imshow("vertical", vertical);
    // Битовая операция инверсии
    cv::bitwise_not(vertical, vertical);
    cv::imshow("vertical_bit", vertical);
    cv::waitKey();

    return 0;
}
