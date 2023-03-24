﻿using NUnit.Framework;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;

namespace SeleniumWD_course
{
    internal class SearchSelectors
    {
        private IWebDriver driver;
        private WebDriverWait wait;

        [SetUp]
        public void start()
        {
            driver = new ChromeDriver();
            wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
        }

        [Test]
        public void ClickLocators()
        {
            driver.Url = "http://localhost/litecart/admin/";
            driver.FindElement(By.Name("username")).SendKeys("admin");
            driver.FindElement(By.Name("password")).SendKeys("admin");
            driver.FindElement(By.Name("login")).Click();
            Thread.Sleep(1000);

            // создание локаторов
            By Locator = By.Id("app-");
            By Docs = By.TagName("li");
            var elements = driver.FindElements(Locator);
            int a = elements.Count();

            // прокликивание элементов меню
            for (int i = 0; i < a; i++)
            {
                // выбор элемента из меню
                elements[i].Click();
                elements = driver.FindElements(Locator);
                driver.FindElement(By.TagName("h1"));

                // выбор внутренних компонентов меню
                var DocsElement = elements[i].FindElements(Docs);
                for (int j = 0; j < DocsElement.Count(); j++)
                {
                    // нажатие на элемент
                    DocsElement[j].Click();
                    elements = driver.FindElements(Locator);
                    DocsElement = elements[i].FindElements(Docs);
                    Thread.Sleep(100);
                    driver.FindElement(By.TagName("h1"));
                }
                Thread.Sleep(250);
            }
            Thread.Sleep(250);
        }

        [TearDown]
        public void stop()
        {
            driver.Quit();
            driver = null;
        }
    }
}