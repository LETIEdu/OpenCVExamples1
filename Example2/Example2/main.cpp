#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

/*
 * Пример работы различных фильтров
 *
 */

// Задержка заголовков в мс
int DELAY_CAPTION = 1500;
// Задержка изображений в мс
int DELAY_BLUR = 400;
// Максимальный размер ядра фильтра
int MAX_KERNEL_LENGTH = 31;
// Исходное изображение
cv::Mat src;
// Результат
cv::Mat dst;
// Название окна
char windowName[] = "Filter Demo";
// Показ заголовка
int displayCaption(const char *caption);
// Показ изображения с задержкой
int displayDst(int delay);

int main()
{
    // Создание окна
    cv::namedWindow(windowName);
    src = cv::imread("../../img/lena.jpg", 1);
    // Отображение заголовка
    if(displayCaption("Original Image") != 0) {return 0;}
    // Копируем полностью исходное изображение
    dst = src.clone();
    // Отображение изображения
    if(displayDst(DELAY_CAPTION) != 0) {return 0;}
    if(displayCaption("Homogeneous Blur") != 0) {return 0;}
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // Равномерный фильтр
        cv::blur(src,              // Исходное изображение
                 dst,              // Результат
                 cv::Size(i, i),   // Размер сканирующего окна
                 cv::Point(-1, -1) // Координаты якоря (-1, -1) - центр
                 );
        if(displayDst(DELAY_BLUR) != 0) {return 0;}
    }
    if(displayCaption("Gaussian Blur") != 0) {return 0;}
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // Фильтр Гаусса
        // Если сигмы равны 0, то они расчитываются из
        // размера сканирующего окна (размер окна примерно равен 3 сигма)
        cv::GaussianBlur(src,            // Исходное изображение
                         dst,            // Результат
                         cv::Size(i, i), // Размер окна
                         0,              // Сигма по оси икс
                         0);             // Сигма по оси игрик
        if(displayDst(DELAY_BLUR) != 0) {return 0;}
    }
    if(displayCaption("Median Blur") != 0) {return 0;}
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // Медианный фильтр
        cv::medianBlur(src, // Исходное изображение
                       dst, // Результат
                       i);  // Размер сканирующего окна
        if(displayDst(DELAY_BLUR) != 0) {return 0;}
    }
    if(displayCaption("Bilateral Blur") != 0) {return 0;}
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // Билатеральный фильтр
        cv::bilateralFilter(src,  // Исходное изображение
                            dst,  // Резуьтат
                            i,    // Диаметр окрестности пикселя при расчёте
                            i*2,  // Чем выше, тем более разные цвета принимаются за одну область
                            i/2); // Размер для сканирующего окна Фильтра Гаусса
        if(displayDst(DELAY_BLUR) != 0) {return 0;}
    }
    displayCaption("End: Press a key!");
    cv::waitKey();
    return 0;
}

// Показ заголовка
int displayCaption(const char* caption)
{
    // Создание матрицы из 0-ей размером с исходное изображение
    dst = cv::Mat::zeros(src.size(), src.type());
    // Добавление текста на изображение
    cv::putText(dst,                               // Исходное изображение
                caption,                           // Текст
                cv::Point(src.cols/4, src.rows/2), // Расположение текста
                cv::FONT_HERSHEY_COMPLEX,          // Шрифт
                1,                                 // Размер шрифта
                cv::Scalar(255, 255, 255)          // Цвет (белый)
                );
    cv::imshow(windowName, dst);
    // Ожидание нажатия клавиши
    int c = cv::waitKey(DELAY_CAPTION);
    // Если нажат Esc, то выход из программы
    if(c == 27) {return -1;}
    return 0;
}

// Показ изображения с задержкой
int displayDst(int delay)
{
    cv::imshow(windowName, dst);
    // Ожидание нажатия клавиши
    int c = cv::waitKey(delay);
    // Если нажат Esc, то выход из программы
    if(c == 27) {return -1;}

    return 0;
}
