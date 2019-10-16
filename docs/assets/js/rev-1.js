var nav = {
  element: undefined,
  expanded: false,

  toggle: function () {
    console.log("toggle");

    if (this.element == undefined) {
      this.element = document.getElementById ('nav');
    }

    if (this.element != undefined) {
      this.expanded = !this.expanded;

      if (this.expanded) {
        this.element.classList.add ('overlay');
      } else {
        this.element.classList.remove ('overlay');
      }
    }
  }
}
