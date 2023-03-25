from lxml import etree


def print_element(element):
    print(element.tag, element.attrib, element.text)

    for child in element:
        print_element(child)


def main():
    xml = etree.parse("conf.xml")
    root = xml.getroot()
    print_element(root)


main()
