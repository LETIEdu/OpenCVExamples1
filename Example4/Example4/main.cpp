#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
 * Детектор границ Canny
 *
 */

cv::Mat src;
cv::Mat tmp;
cv::Mat edges;
cv::Mat result;
int minThresh = 0;

// Функция, вызываемая при перемещении ползунка
void applyCanny(int, void*)
{
    cv::Canny(tmp,          // Исходное изображение
              edges,        // Результат
              minThresh,    // Нижний порог
              minThresh * 3 // Верхний порог
              );
    // Обнуляем всё изображение результата
    result = cv::Scalar::all(0);
    // Копируем пиксели из исходного изображения, используя
    // найденные границы как маску
    src.copyTo(result, edges);

    cv::imshow("Original", src);
    cv::imshow("tmp", tmp);

    cv::imshow("Canny", result);
}

int main()
{
    src = cv::imread("../../img/lena.jpg");
    result.create(src.size(), src.type());
    // Создаём окно
    cv::namedWindow("Canny");
    // Добавляем ползунок к окну и связываем его с переменной
    // Функция, адрес которой передаётся в cv::createTrackbar,
    // автоматически вызывается при изменении положения ползунка
    cv::createTrackbar("MinThresh", // Название ползунка
                       "Canny",     // Имя окна
                       &minThresh,  // Адрес переменной
                       100,         // Максимальное значение
                       applyCanny   // указатель на функцию
                       );
    cv::cvtColor(src, tmp, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(tmp, tmp, cv::Size(5, 5), 1);
    applyCanny(0, 0);
    cv::waitKey();

    return 0;
}
