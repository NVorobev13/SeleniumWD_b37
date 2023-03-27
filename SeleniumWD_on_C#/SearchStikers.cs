using NUnit.Framework;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;

namespace SeleniumWD_course
{
    internal class SearchStiker
    {
        private IWebDriver driver;
        private WebDriverWait wait;

        [SetUp]
        public void Start()
        {
            driver = new ChromeDriver();
            wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
        }

        [Test]
        public void CheckStikers()
        {
            driver.Url = "http://localhost/litecart/";

            //создаем локаторы
            By MostPopular = By.Id("box-most-popular");
            By Campaigns = By.Id("box-campaigns");
            By LatestProducts = By.Id("box-latest-products");

            //проверяем MostPopular
            var elements = driver.FindElement(MostPopular);
            var MostPopEl = elements.FindElement(By.TagName("ul")).FindElements(By.TagName("li"));
            for (int i = 0; i < MostPopEl.Count(); i++)
            {
                var PopElStickerCheck = MostPopEl[i].FindElements(By.ClassName("sticker"));
                if (PopElStickerCheck.Count() != 1)
                {
                    Console.WriteLine("Popular: sticker error");
                }
                else if (PopElStickerCheck.Count() == 1)
                {
                    Console.WriteLine("Popular: sticker yes");
                }
            }

            //проверяем Campaigns
            elements = driver.FindElement(Campaigns);
            var CampsEl = elements.FindElement(By.TagName("ul")).FindElements(By.TagName("li"));
            for (int i = 0; i < CampsEl.Count(); i++)
            {
                var CampElStickerCheck = CampsEl[i].FindElements(By.ClassName("sticker"));
                if (CampElStickerCheck.Count() != 1)
                {
                    Console.WriteLine("Campaigns: sticker error");
                }
                else if (CampElStickerCheck.Count() == 1)
                {
                    Console.WriteLine("Campaigns: sticker yes");
                }

            }

            //проверяем LatestProducts
            elements = driver.FindElement(LatestProducts);
            var LatestProdEl = elements.FindElement(By.TagName("ul")).FindElements(By.TagName("li"));
            for (int i = 0; i < LatestProdEl.Count(); i++)
            {
                var LatestElStickerCheck = LatestProdEl[i].FindElements(By.ClassName("sticker"));
                if (LatestElStickerCheck.Count() != 1)
                {
                    Console.WriteLine("LatestProducts: sticker error");
                }
                else if (LatestElStickerCheck.Count() == 1)
                {
                    Console.WriteLine("LatestProducts: sticker yes");
                }
            }
        }

        [TearDown]
        public void Stop()
        {
            driver.Quit();
            driver = null;
        }
    }
}