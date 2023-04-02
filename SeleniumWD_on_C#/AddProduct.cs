using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium;

namespace SeleniumWD_course
{
    internal class AddProduct
    {
        private IWebDriver driver;
        private WebDriverWait wait;

        [SetUp]
        public void StartBrowser()
        {
            driver = new ChromeDriver();
            wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
        }

        [Test]
        public void StartSearch()
        {
            int value = new Random().Next(1488, 7699);
            driver.Url = "http://localhost/litecart/admin/";
            driver.FindElement(By.Name("username")).SendKeys("admin");
            driver.FindElement(By.Name("password")).SendKeys("admin");
            driver.FindElement(By.Name("login")).Click();
            Thread.Sleep(1000);
            driver.FindElement(By.XPath("//ul[@id='box-apps-menu']/li[2]/a")).Click();
            driver.FindElement(By.XPath(".//*[@id=\"content\"]/div[1]/a[2]")).Click();
            Thread.Sleep(1000);

            //заполнение полей General
            var ProductStatus = driver.FindElement(By.XPath(".//div[@id='tab-general']/table/tbody/tr[1]/td/label[1]/input"));
            var ProductName = driver.FindElement(By.XPath(".//*[@id=\"tab-general\"]/table/tbody/tr[2]/td/span/input"));
            var ProductCode = driver.FindElement(By.XPath(".//*[@id=\"tab-general\"]/table/tbody/tr[3]/td/input"));
            var ProductQuantity = driver.FindElement(By.XPath(".//*[@id=\"tab-general\"]/table/tbody/tr[8]/td/table/tbody/tr/td[1]/input"));
            var ProductCategories = driver.FindElement(By.XPath(".//div[@id='tab-general']/table/tbody/tr[4]/td/div/table/tbody/tr[2]/td[1]/input"));
            var ProductDefCategory = driver.FindElement(By.XPath(".//div[@id='tab-general']/table/tbody/tr[4]/td/div/table/tbody/tr[1]/td[1]/input"));
            var ProductImagePath = driver.FindElement(By.XPath(".//div[@id='tab-general']/table/tbody/tr[9]//input"));
            var ProductImage = driver.FindElement(By.XPath(".//div[@id='tab-general']/table/tbody/tr[9]//a"));
            var ProductDateValidF = driver.FindElement(By.XPath(".//div[@id='tab-general']/table/tbody/tr[10]//input"));
            var ProductDateValidT = driver.FindElement(By.XPath(".//div[@id='tab-general']/table/tbody/tr[11]//input"));

            string TextProdName = "Product" + value;
            string TextProdCode = "Code" + value;
            string TextProdQuantity = value.ToString();
            string PathProdtImage = Path.GetFileName("sobaken.png");
            string TextProdDateValidF = "01042023";
            string TextProdDateValidT = "01122023";

            
            ProductStatus.Click(); 
            ProductName.SendKeys(TextProdName);
            ProductCode.SendKeys(TextProdCode);
            ProductCategories.Click();
            ProductDefCategory.Click();
            ProductQuantity.SendKeys(TextProdQuantity);
            ProductImagePath.SendKeys(PathProdtImage);
            ProductImage.Click();
            ProductDateValidF.SendKeys(TextProdDateValidF);
            ProductDateValidT.SendKeys(TextProdDateValidT);

            //заполнение полей Information
            driver.FindElement(By.XPath(".//*[@id=\"content\"]/form/div/ul/li[2]/a")).Click();
            Thread.Sleep(2000);
            SelectElement ProductManufacturer = new SelectElement(driver.FindElement(By.XPath(".//select[@name='manufacturer_id']")));
            var ProductKeywords = driver.FindElement(By.XPath(".//input[@name='keywords']"));
            var ProductShortDescription = driver.FindElement(By.XPath(".//input[@name='short_description[en]']")); ;
            var ProductDescription = driver.FindElement(By.XPath(".//div[@class='trumbowyg-editor']")); ;
            var ProductHeadTitle = driver.FindElement(By.XPath(".//input[@name='head_title[en]']")); ;
            var ProductMetaDescription = driver.FindElement(By.XPath(".//input[@name='meta_description[en]']"));

            string TextProdKeywords = "Product" + value;
            string TextProdShortDescription = "Description" + value;

            ProductManufacturer.SelectByValue("1");
            ProductKeywords.SendKeys(TextProdKeywords);
            ProductShortDescription.SendKeys(TextProdShortDescription);
            ProductDescription.SendKeys("UsersTest");
            ProductHeadTitle.SendKeys("UsersTest");
            ProductMetaDescription.SendKeys("UsersTest");
            Thread.Sleep(2000);

            //заполнение полей Prices
            driver.FindElement(By.XPath(".//*[@id=\"content\"]/form/div/ul/li[4]/a")).Click();
            var ProductPurchasePrice = driver.FindElement(By.XPath(".//*[@id=\"tab-prices\"]/table[1]/tbody/tr/td/input"));
            SelectElement ProductPurchasePriceV = new SelectElement(driver.FindElement(By.XPath(".//*[@id=\"tab-prices\"]/table[1]/tbody/tr/td/select")));
            var ProductPriceUSD = driver.FindElement(By.XPath(".//*[@id=\"tab-prices\"]/table[3]/tbody/tr[2]/td[1]/span/input"));
            var ProductPriceEUR = driver.FindElement(By.XPath(".//*[@id=\"tab-prices\"]/table[3]/tbody/tr[3]/td[1]/span/input"));

            ProductPurchasePrice.SendKeys(TextProdQuantity);
            ProductPurchasePriceV.SelectByValue("USD");
            ProductPriceUSD.SendKeys(TextProdQuantity);
            ProductPriceEUR.SendKeys(TextProdQuantity);
            Thread.Sleep(2000);

            //сохранение добавленного продукта
            driver.FindElement(By.XPath(".//*[@id=\"content\"]/form/p/span/button[1]")).Click(); 
            Thread.Sleep(1000);

            Console.WriteLine("В системе создана новая товарная позиция.");
            Console.WriteLine("-----------------------------------------");
            Console.WriteLine("Название: " + TextProdName);
            Console.WriteLine("Описание: " + TextProdShortDescription);
            Console.WriteLine("Цена: " + TextProdQuantity);
            Console.WriteLine("Товарный код: " + TextProdCode);
        }

        [TearDown]
        public void end()
        {
            driver.Quit();
            driver = null;
        }
    }
}
